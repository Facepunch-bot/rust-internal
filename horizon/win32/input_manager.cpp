#include "input_manager.hpp"
#include "trace.hpp"

#include "../memory/operation.hpp"

namespace horizon::win32
{

InputManager::~InputManager()
{
	Destroy();
}

void InputManager::Destroy()
{
	m_events.clear();
}

WindowEvent* InputManager::Find( std::uint64_t hash )
{
	if( m_events.empty() )
	{
		TRACE( "%s: m_events is empty!", FN );
		return nullptr;
	}

	for( auto& entry : m_events )
	{
		if( entry.m_hash == hash )
		{
			return &entry;
		}
	}

	return nullptr;
}

const WindowEvent* InputManager::Find( std::uint64_t hash ) const
{
	if( m_events.empty() )
	{
		TRACE( "%s: m_events is empty!", FN );
		return nullptr;
	}

	for( const auto& entry : m_events )
	{
		if( entry.m_hash == hash )
		{
			return &entry;
		}
	}

	return nullptr;
}

bool InputManager::RegisterEvent( std::uint64_t hash, WindowEvent::MessageFn message )
{
	if( !memory::IsAddressValid( message ) )
	{
		TRACE( "%s: message is not valid!", FN );
		return false;
	}

	const auto window_event = Find( hash );

	if( memory::IsAddressValid( window_event ) )
	{
		TRACE( "%s: Event '0x%016llX' already exists!", FN, hash );
		return true;
	}

	m_events.push_back( { hash, message } );
	return true;
}

void InputManager::UnregisterEvent( std::uint64_t hash )
{
	auto window_event = Find( hash );

	if( memory::IsAddressValid( window_event ) )
	{
		TRACE( "%s: Event '0x%016llX' is not valid!", FN, hash );
		return;
	}

	window_event->m_message = nullptr;
}

bool InputManager::ProcessMessage( HWND window, std::uint32_t message, std::uintptr_t wparam, std::intptr_t lparam )
{
	auto input = false;

	for( auto& window_event : m_events )
	{
		if( memory::IsAddressValid( window_event.m_message ) )
		{
			input |= window_event.m_message( window, message, wparam, lparam );
		}
	}

	return input;
}

bool InputManager::OnDispatchMessage( const MSG* msg )
{
	if( !memory::IsAddressValid( msg ) )
	{
		return false;
	}

	auto input = false;

	for( auto& window_event : m_events )
	{
		if( memory::IsAddressValid( window_event.m_message ) )
		{
			input |= window_event.m_message( msg->hwnd, msg->message, msg->wParam, msg->lParam );
		}
	}

	return input;
}

} // namespace horizon::win32