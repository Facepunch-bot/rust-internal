#include "thread_safe_statics.hpp"

#include "../memory/operation.hpp"

#include "../win32/trace.hpp"

using namespace horizon;

vcruntime::ThreadSafeStatics* g_thread_safe_statics = nullptr;

extern "C"
{

	std::int32_t _Init_global_epoch = std::numeric_limits< std::int32_t >::min();
	ATOM_THREAD std::int32_t _Init_thread_epoch = std::numeric_limits< std::int32_t >::min();

}; // extern "C"

namespace horizon::vcruntime
{

namespace constant
{
constexpr auto BeingInitialized = static_cast< std::int32_t >( -1 );
constexpr auto Uninitialized = static_cast< std::int32_t >( 0 );
}

ThreadSafeStatics::ThreadSafeStatics() noexcept
	: m_epoch( nullptr )
	, m_epoch_thread( nullptr )
	, m_mutex( 4000 )
	, m_condition_variable()
{ }

bool ThreadSafeStatics::Initialize() noexcept
{
	m_epoch = std::addressof( _Init_global_epoch );

	if( !memory::IsAddressValid( m_epoch ) )
	{
		TRACE( "%s: m_epoch is not valid!", ATOM_FUNCTION );
		return false;
	}

	m_epoch_thread = std::addressof( _Init_thread_epoch );
	
	if( !memory::IsAddressValid( m_epoch_thread ) )
	{
		TRACE( "%s: m_epoch_thread is not valid!", ATOM_FUNCTION );
		return false;
	}

	SetEpoch( std::numeric_limits< std::int32_t >::min() );
	SetEpochThread( std::numeric_limits< std::int32_t >::min() );
	return true;
}

void ThreadSafeStatics::Uninitialize() noexcept
{ }

void ThreadSafeStatics::OnThreadHeader( std::int32_t& initializer ) noexcept
{
	core::ScopedLock lock( m_mutex );

	if( initializer == constant::Uninitialized )
	{
		initializer = constant::BeingInitialized;
	}
	else
	{
		while( initializer == constant::BeingInitialized )
		{
			m_condition_variable.wait_for( m_mutex, 100 );

			if( initializer == constant::Uninitialized )
			{
				initializer = constant::BeingInitialized;
				return;
			}
		}

		UpdateThread();
	}
}

void ThreadSafeStatics::OnThreadAbort( std::int32_t& initializer ) noexcept
{
	// guard
	{
		core::ScopedLock lock( m_mutex );
		initializer = constant::Uninitialized;
	}

	m_condition_variable.notify();
}

void ThreadSafeStatics::OnThreadFooter( std::int32_t& initializer ) noexcept
{
	// guard
	{
		core::ScopedLock lock( m_mutex );

		Update();
		initializer = GetEpoch();
		UpdateThread();
	}

	m_condition_variable.notify();
}

void ThreadSafeStatics::Update() noexcept
{
	const auto epoch = GetEpoch();
	SetEpoch( epoch + 1 );
}

void ThreadSafeStatics::UpdateThread() noexcept
{
	const auto epoch = GetEpoch();
	SetEpochThread( epoch );
}

void ThreadSafeStatics::SetEpoch( std::int32_t epoch ) noexcept
{
	*m_epoch = epoch;
}

void ThreadSafeStatics::SetEpochThread( std::int32_t epoch_thread ) noexcept
{
	*m_epoch_thread = epoch_thread;
}

std::int32_t ThreadSafeStatics::GetEpoch() const noexcept
{
	return *m_epoch;
}

std::int32_t ThreadSafeStatics::GetEpochThread() const noexcept
{
	return *m_epoch_thread;
}

} // namespace horizon::vcruntime

extern "C"
{

	void _Init_thread_header( std::int32_t* const parameter ) noexcept
	{
		if( !memory::IsAddressValid( parameter ) )
		{
			return;
		}

		if( !memory::IsAddressValid( g_thread_safe_statics ) )
		{
			return;
		}

		g_thread_safe_statics->OnThreadHeader( *parameter );
	}

	void _Init_thread_abort( std::int32_t* const parameter ) noexcept
	{
		if( !memory::IsAddressValid( parameter ) )
		{
			return;
		}

		if( !memory::IsAddressValid( g_thread_safe_statics ) )
		{
			return;
		}

		g_thread_safe_statics->OnThreadAbort( *parameter );
	}

	void _Init_thread_footer( std::int32_t* const parameter ) noexcept
	{
		if( !memory::IsAddressValid( parameter ) )
		{
			return;
		}

		if( !memory::IsAddressValid( g_thread_safe_statics ) )
		{
			return;
		}

		g_thread_safe_statics->OnThreadFooter( *parameter );
	}

}; // extern "C"