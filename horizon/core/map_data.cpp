#include "map_data.hpp"

#include "../win32/basic.hpp"
#include "../win32/time.hpp"

namespace horizon::core
{

bool MapData::Create()
{
	const auto image_native = win32::GetImage( HASH( L"ntdll.dll" ) );

	if( memory::IsUserAddress( image_native ) )
	{
		RtlAddFunctionTable.Set( image_native );
		RtlDeleteFunctionTable.Set( image_native );
		RtlAllocateHeap.Set( image_native );
		RtlReAllocateHeap.Set( image_native );
		RtlFreeHeap.Set( image_native );
		RtlQueryPerformanceCounter.Set( image_native );
		RtlQueryPerformanceFrequency.Set( image_native );
		RtlInitializeCriticalSection.Set( image_native );
		RtlInitializeCriticalSectionEx.Set( image_native );
		RtlEnterCriticalSection.Set( image_native );
		RtlTryEnterCriticalSection.Set( image_native );
		RtlLeaveCriticalSection.Set( image_native );
		RtlDeleteCriticalSection.Set( image_native );

		if( IsValidConditionVariable() )
		{
			RtlInitializeConditionVariable.Set( image_native );
			RtlSleepConditionVariableCS.Set( image_native );
			RtlWakeConditionVariable.Set( image_native );
			RtlWakeAllConditionVariable.Set( image_native );
		}

		const auto exception_procedure = *reinterpret_cast< std::uintptr_t* >( &__C_specific_handler );
		const auto exception_procedure_pointer = reinterpret_cast< std::uintptr_t* >( &__C_specific_handler );

		if( exception_procedure )
		{
			( *exception_procedure_pointer ) = ( image_native + exception_procedure );
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	const auto image_kernel32 = win32::GetImage( HASH( L"kernel32.dll" ) );

	if( memory::IsUserAddress( image_kernel32 ) )
	{
		OutputDebugStringA.Set( image_kernel32 );
		OutputDebugStringW.Set( image_kernel32 );
	}
	else
	{
		return false;
	}

	const auto image_msvcrt = win32::GetImage( HASH( L"msvcrt.dll" ) );

	if( memory::IsUserAddress( image_msvcrt ) )
	{
		malloc.Set( image_msvcrt );
		free.Set( image_msvcrt );
		memchr.Set( image_msvcrt );
		memcmp.Set( image_msvcrt );
		memcpy.Set( image_msvcrt );
		memmove.Set( image_msvcrt );
		memset.Set( image_msvcrt );
		qsort.Set( image_msvcrt );
		strstr.Set( image_msvcrt );
		_vsnprintf_l.Set( image_msvcrt );
		_vsnwprintf_l.Set( image_msvcrt );
		fabs.Set( image_msvcrt );
		fmod.Set( image_msvcrt );
		pow.Set( image_msvcrt );
		atan2.Set( image_msvcrt );
		ceil.Set( image_msvcrt );
		floor.Set( image_msvcrt );
		atol.Set( image_msvcrt );
		atof.Set( image_msvcrt );

		const auto sscanf_procedure = *reinterpret_cast< std::uintptr_t* >( &sscanf );
		const auto sscanf_procedure_pointer = reinterpret_cast< std::uintptr_t* >( &sscanf );

		if( sscanf_procedure )
		{
			( *sscanf_procedure_pointer ) = ( image_msvcrt + sscanf_procedure );
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

void MapData::Destroy()
{
	// 
	// reset instance fields
	// 
	std::memset( this, 0, sizeof( MapData ) );
}

bool MapData::IsValid() const
{
	return ( m_signature == HASH( "MapData" ) );
}

bool MapData::IsValidSubscription()
{
	LARGE_INTEGER time = { };
	RtlQueryPerformanceCounter( &time );
	return ( time.QuadPart < m_time.QuadPart );
}

bool MapData::IsValidConditionVariable() const
{
	return ( RtlInitializeConditionVariable.IsValid() &&
					 RtlSleepConditionVariableCS.IsValid() &&
					 RtlWakeConditionVariable.IsValid() &&
					 RtlWakeAllConditionVariable.IsValid() );
}

} // namespace horizon::core

horizon::core::MapData g_map_data = { };