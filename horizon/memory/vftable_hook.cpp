#include "vftable_hook.hpp"

#include "../memory/operation.hpp"

#include "../win32/trace.hpp"
#include "../win32/image.hpp"
#include "../win32/process.hpp"

namespace horizon::memory
{

VFTableHook::VFTableHook( void* instance )
{
	if( !Create( instance ) )
	{
		TRACE( "%s: Create( 0x%016llX ) error!", FN, ToAddress( instance ) );
	}
}

VFTableHook::~VFTableHook()
{
	Destroy();
}

bool VFTableHook::Create( void* instance )
{
	Destroy();

	m_instance = reinterpret_cast< std::uintptr_t** >( instance );

	if( !IsAddressValid( m_instance ) )
		return false;

	m_restore = *m_instance;

	if( !IsAddressValid( m_restore ) )
		return false;

	while( IsAddressValid( m_restore[ m_size ] ) )
	{
		m_size++;
	}

	if( !m_size )
	{
		return false;
	}

	m_replace = new std::uintptr_t[ m_size ];
	std::memcpy( m_replace, m_restore, m_size * sizeof( std::uintptr_t ) );

	*m_instance = m_replace;
	
	return true;
}

void VFTableHook::Destroy()
{
	if( IsAddressValid( m_instance ) )
	{
		if( IsAddressValid( m_restore ) )
		{
			*m_instance = m_restore;
		}
	}

	SafeDeleteArray( m_replace );

	m_instance = nullptr;
	m_restore = nullptr;
	m_replace = nullptr;
	m_size = 0;
}

void* VFTableHook::GetInstance() const
{
	return m_instance;
}

void VFTableHook::Hook( void* procedure, std::size_t index )
{
	if( !m_replace || index >= m_size )
	{
		return;
	}

	m_replace[ index ] = reinterpret_cast< std::uintptr_t >( procedure );
}

void VFTableHook::Unhook( std::size_t index )
{
	if( !m_replace || index >= m_size )
	{
		return;
	}

	m_replace[ index ] = m_restore[ index ];
}

}