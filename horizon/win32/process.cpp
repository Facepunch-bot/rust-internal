#include "process.hpp"

#include "../core/map_data.hpp"
#include "../memory/operation.hpp"
#include "../win32/trace.hpp"

namespace horizon::win32
{

HANDLE NtCurrentProcess() noexcept
{
	constexpr std::intptr_t current_process = -1;
	return reinterpret_cast< const HANDLE >( current_process );
}

HANDLE NtCurrentThread() noexcept
{
	constexpr std::intptr_t current_thread = -2;
	return reinterpret_cast< const HANDLE >( current_thread );
}

HANDLE NtCurrentSession() noexcept
{
	constexpr std::intptr_t current_session = -3;
	return reinterpret_cast< const HANDLE >( current_session );
}

TEB* NtCurrentTeb() noexcept
{
	auto teb = static_cast< std::uintptr_t >( 0 );
	auto displacement = static_cast< std::uint32_t >( FIELD_OFFSET( NT_TIB, Self ) );

#if defined( HORIZON_X86 )
	teb = __readfsdword( displacement );
#elif defined( HORIZON_X64 )
	teb = __readgsqword( displacement );
#endif // HORIZON_X86

	return reinterpret_cast< TEB* >( teb );
}

PEB* NtCurrentPeb() noexcept
{
	const auto teb = NtCurrentTeb();

	if( memory::IsAddressValid( teb ) )
	{
		return teb->ProcessEnvironmentBlock;
	}

	return nullptr;
}

std::uint32_t NtCurrentProcessId() noexcept
{
	const auto teb = NtCurrentTeb();

	if( memory::IsAddressValid( teb ) )
	{
		const auto process_id = memory::ToAddress( teb->ClientId.UniqueProcess );
		return static_cast< std::uint32_t >( process_id );
	}

	return 0;
}

std::uint32_t NtCurrentThreadId() noexcept
{
	const auto teb = NtCurrentTeb();

	if( memory::IsAddressValid( teb ) )
	{
		const auto thread_id = memory::ToAddress( teb->ClientId.UniqueThread );
		return static_cast< std::uint32_t >( thread_id );
	}

	return 0;
}

std::int32_t GetLastStatus() noexcept
{
	const auto teb = NtCurrentTeb();

	if( memory::IsAddressValid( teb ) )
	{
		return static_cast< std::int32_t >( teb->LastStatusValue );
	}

	return STATUS_INVALID_THREAD;
}

void SetLastStatus( std::int32_t last_status ) noexcept
{
	const auto teb = NtCurrentTeb();

	if( memory::IsAddressValid( teb ) )
	{
		teb->LastStatusValue = static_cast< std::uint32_t >( last_status );
	}
}

std::uint32_t GetLastError() noexcept
{
	const auto teb = NtCurrentTeb();

	if( memory::IsAddressValid( teb ) )
	{
		return teb->LastErrorValue;
	}

	return ERROR_INVALID_THREAD_ID;
}

void SetLastError( std::uint32_t last_error ) noexcept
{
	const auto teb = NtCurrentTeb();

	if( memory::IsAddressValid( teb ) )
	{
		teb->LastErrorValue = last_error;
	}
}

void* GetProcessHeap() noexcept
{
	const auto peb = NtCurrentPeb();

	if( memory::IsAddressValid( peb ) )
	{
		return peb->ProcessHeap;
	}

	return nullptr;
}

void* RtlAllocateHeap( void* heap_handle, std::uint32_t flags, std::size_t size ) noexcept
{
	if( !heap_handle )
	{
		TRACE( "%s: heap_handle is nullptr!", ATOM_FUNCTION );
		return nullptr;
	}

	return g_map_data.RtlAllocateHeap( heap_handle, flags, size );
}

void* RtlReAllocateHeap( void* heap_handle, std::uint32_t flags, void* memory_pointer, std::size_t size )
{
	if( !heap_handle )
	{
		TRACE( "%s: heap_handle is nullptr!", ATOM_FUNCTION );
		return nullptr;
	}

	return g_map_data.RtlReAllocateHeap( heap_handle, flags, memory_pointer, size );
}

bool RtlFreeHeap( void* heap_handle, std::uint32_t flags, void* memory_pointer ) noexcept
{
	if( !heap_handle )
	{
		TRACE( "%s: heap_handle is nullptr!", ATOM_FUNCTION );
		return false;
	}

	if( !memory_pointer )
	{
		TRACE( "%s: memory_pointer is nullptr!", ATOM_FUNCTION );
		return false;
	}

	return g_map_data.RtlFreeHeap( heap_handle, flags, memory_pointer );
}

} // namespace horizon::win32