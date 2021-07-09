#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "../core/singleton.hpp"

namespace horizon::win32
{

struct WindowEvent
{
	using MessageFn = bool( * )( const void* window, std::uint32_t message, std::uintptr_t wparam, std::intptr_t lparam );

	WindowEvent()
		: m_hash( 0 )
		, m_message( nullptr )
	{ }

	WindowEvent( std::uint64_t hash, MessageFn message )
		: m_hash( hash )
		, m_message( message )
	{ }

	std::uint64_t m_hash = 0;
	MessageFn m_message = nullptr;
};

class InputManager : public core::Singleton< InputManager >
{
public:
	~InputManager();

public:
	void Destroy();

public:
	WindowEvent* Find( std::uint64_t hash );
	const WindowEvent* Find( std::uint64_t hash ) const;

	bool RegisterEvent( std::uint64_t hash, WindowEvent::MessageFn message );
	void UnregisterEvent( std::uint64_t hash );

public:
	bool ProcessMessage( HWND window, std::uint32_t message, std::uintptr_t wparam, std::intptr_t lparam );
	bool OnDispatchMessage( const MSG* msg );

protected:
	POINT	m_mouse = { };
	std::vector< WindowEvent > m_events = { };
};


} // namespace horizon::win32