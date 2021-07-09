#include "mutex.hpp"

#include "../core/map_data.hpp"

#include "../memory/operation.hpp"
#include "../memory/secure_call.hpp"
#include "../memory/system_call.hpp"

#include "../win32/basic.hpp"
#include "../win32/image.hpp"
#include "../win32/process.hpp"
#include "../win32/trace.hpp"

namespace horizon::core
{

Mutex::Mutex( std::int32_t spin_count /*= 0*/ )
	: m_section()
{
	if( !win32::RtlInitializeCriticalSectionEx( &m_section, spin_count, 0 ) )
	{
		TRACE( "%s: RtlInitializeCriticalSectionEx( ... ) error!", ATOM_FUNCTION );
	}
}

Mutex::~Mutex()
{
	if( !win32::RtlDeleteCriticalSection( &m_section ) )
	{
		TRACE( "%s: RtlDeleteCriticalSection( ... ) error!", ATOM_FUNCTION );
	}
}

void Mutex::lock()
{
	if( !win32::RtlEnterCriticalSection( &m_section ) )
	{
		TRACE( "%s: RtlEnterCriticalSection( ... ) error!", ATOM_FUNCTION );
	}
}

bool Mutex::try_lock()
{
	return win32::RtlTryEnterCriticalSection( &m_section );
}

void Mutex::unlock()
{
	if( !win32::RtlLeaveCriticalSection( &m_section ) )
	{
		TRACE( "%s: RtlLeaveCriticalSection( ... ) error!", ATOM_FUNCTION );
	}
}

ScopedLock::ScopedLock( Mutex& mutex )
	: m_mutex( mutex )
{
	m_mutex.lock();
}

ScopedLock::~ScopedLock()
{
	m_mutex.unlock();
}

ConditionVariable::ConditionVariable()
	: m_cv()
	, m_event( nullptr )
{
	if( g_map_data.IsValidConditionVariable() )
	{
		win32::RtlInitializeConditionVariable( &m_cv );
	}
	else
	{
		win32::OBJECT_ATTRIBUTES object_attributes = { };
		win32::InitializeObjectAttributes( &object_attributes );

		const auto status = g_map_data.NtCreateEvent( &m_event, EVENT_ALL_ACCESS, &object_attributes, win32::NotificationEvent, true );

		if( !NT_SUCCESS( status ) )
		{
			TRACE( "%s: NtCreateEvent( ... ) error! (0x%08X)", ATOM_FUNCTION, status );
		}
	}
}

ConditionVariable::~ConditionVariable()
{
	if( g_map_data.IsValidConditionVariable() )
	{
		return;
	}

	if( m_event && m_event != INVALID_HANDLE_VALUE )
	{
		const auto status = g_map_data.NtClose( m_event );

		if( !NT_SUCCESS( status ) )
		{
			TRACE( "%s: NtClose( ... ) error! (0x%08X)", ATOM_FUNCTION, status );
		}
	}
}

void ConditionVariable::notify()
{
	if( g_map_data.IsValidConditionVariable() )
	{
		win32::RtlWakeAllConditionVariable( &m_cv );
	}
	else
	{
		if( !m_event || m_event == INVALID_HANDLE_VALUE )
		{
			TRACE( "%s: m_event is not valid!", ATOM_FUNCTION );
			return;
		}

		auto status = g_map_data.NtSetEvent( m_event, nullptr );

		if( !NT_SUCCESS( status ) )
		{
			TRACE( "%s: NtSetEvent( ... ) error! (0x%08X)", ATOM_FUNCTION, status );
			return;
		}

		status = g_map_data.NtResetEvent( m_event, nullptr );

		if( !NT_SUCCESS( status ) )
		{
			TRACE( "%s: NtResetEvent( ... ) error! (0x%08X)", ATOM_FUNCTION, status );
		}
	}
}

bool ConditionVariable::wait_for( Mutex& mutex, std::uint32_t time )
{
	win32::LARGE_INTEGER time_out = { };
	time_out.QuadPart = static_cast< std::int64_t >( time ) * -( 10000 );

	if( g_map_data.IsValidConditionVariable() )
	{
		if( !win32::RtlSleepConditionVariableCS( &m_cv, &mutex.m_section, &time_out ) )
		{
			TRACE( "%s: RtlSleepConditionVariableCS( ... ) error!", ATOM_FUNCTION );
			return false;
		}
	}
	else
	{
		mutex.unlock();

		const auto status = g_map_data.NtWaitForSingleObject( m_event, false, &time_out );

		if( !NT_SUCCESS( status ) )
		{
			mutex.unlock();
			TRACE( "%s: NtWaitForSingleObject( ... ) error! (0x%08X)", ATOM_FUNCTION, status );
			return false;
		}

		mutex.lock();
	}

	return true;
}

} // namespace horizon::win32