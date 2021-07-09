#include "basic.hpp"
#include "process.hpp"
#include "trace.hpp"

#include "../constant/character.hpp"
#include "../constant/hash.hpp"
#include "../constant/secure_string.hpp"
#include "../constant/string.hpp"

#include "../core/map_data.hpp"

#include "../memory/operation.hpp"

#include "sdk/list_entry.hpp"
#include "sdk/large_integer.hpp"
#include "sdk/rtl_critical_section.hpp"
#include "sdk/rtl_critical_section_debug.hpp"

namespace horizon::win32
{

constexpr std::uint32_t UserSharedData32 = 0x7FFE0000;
constexpr std::uint64_t UserSharedData64 = 0x000000007FFE0000;

#if defined( HORIZON_X32 )
constexpr std::uintptr_t UserSharedData = UserSharedData32;
#elif defined( HORIZON_X64 )
constexpr std::uintptr_t UserSharedData = UserSharedData64;
#endif // HORIZON_X32

KUSER_SHARED_DATA* GetUserSharedData()
{
	const auto user_shared_data = memory::ToPointer( UserSharedData );
	return static_cast< KUSER_SHARED_DATA* >( user_shared_data );
}

void InitializeString( STRING* destination, const char* const source )
{
	if( memory::IsAddressValid( destination ) )
	{
		if( memory::IsAddressValid( source ) )
		{
			const auto length = constant::GetLength( source );

			destination->Length = static_cast< std::uint16_t >( length * sizeof( char ) );
			destination->MaximumLength = destination->Length + sizeof( char );
		}
		else
		{
			destination->Length = 0;
			destination->MaximumLength = 0;
		}

		destination->Buffer = const_cast< char* >( source );
	}
}

void InitializeAnsiString( ANSI_STRING* destination, const char* const source )
{
	if( memory::IsAddressValid( destination ) )
	{
		if( memory::IsAddressValid( source ) )
		{
			const auto length = constant::GetLength( source );

			destination->Length = static_cast< std::uint16_t >( length * sizeof( char ) );
			destination->MaximumLength = destination->Length + sizeof( char );
		}
		else
		{
			destination->Length = 0;
			destination->MaximumLength = 0;
		}

		destination->Buffer = const_cast< char* >( source );
	}
}

void InitializeUnicodeString( UNICODE_STRING* destination, const wchar_t* const source )
{
	if( memory::IsAddressValid( destination ) )
	{
		if( memory::IsAddressValid( source ) )
		{
			const auto length = constant::GetLength( source );

			destination->Length = static_cast< std::uint16_t >( length * sizeof( wchar_t ) );
			destination->MaximumLength = destination->Length + sizeof( wchar_t );
		}
		else
		{
			destination->Length = 0;
			destination->MaximumLength = 0;
		}

		destination->Buffer = const_cast< wchar_t* >( source );
	}
}

void InitializeObjectAttributes( OBJECT_ATTRIBUTES* object_attributes, UNICODE_STRING* object_name /*= nullptr*/, std::uint32_t attributes /*= 0*/, void* security_descriptor /*= nullptr*/, void* security_quality_of_service /*= nullptr*/ )
{
	if( memory::IsAddressValid( object_attributes ) )
	{
		object_attributes->Length = sizeof( OBJECT_ATTRIBUTES );
		object_attributes->RootDirectory = nullptr;
		object_attributes->ObjectName = object_name;
		object_attributes->Attributes = attributes;
		object_attributes->SecurityDescriptor = security_descriptor;
		object_attributes->SecurityQualityOfService = security_quality_of_service;
	}
}

bool RtlAddFunctionTable( IMAGE_RUNTIME_FUNCTION_ENTRY* image_runtime_function_entry, std::uint32_t count, std::uintptr_t image )
{
	return g_map_data.RtlAddFunctionTable( image_runtime_function_entry, count, image );
}

bool RtlDeleteFunctionTable( IMAGE_RUNTIME_FUNCTION_ENTRY* image_runtime_function_entry )
{
	return g_map_data.RtlDeleteFunctionTable( image_runtime_function_entry );
}

bool RtlQueryPerformanceCounter( LARGE_INTEGER* counter )
{
	return g_map_data.RtlQueryPerformanceCounter( counter );
}

bool RtlQueryPerformanceFrequency( LARGE_INTEGER* frequency )
{
	return g_map_data.RtlQueryPerformanceFrequency( frequency );
}

bool RtlInitializeCriticalSection( RTL_CRITICAL_SECTION* section )
{
	return NT_SUCCESS( g_map_data.RtlInitializeCriticalSection( section ) );
}

bool RtlInitializeCriticalSectionEx( RTL_CRITICAL_SECTION* section, std::int32_t spin_count, std::uint32_t flags )
{
	return NT_SUCCESS( g_map_data.RtlInitializeCriticalSectionEx( section, spin_count, flags ) );
}

bool RtlEnterCriticalSection( RTL_CRITICAL_SECTION* section )
{
	return NT_SUCCESS( g_map_data.RtlEnterCriticalSection( section ) );
}

bool RtlTryEnterCriticalSection( RTL_CRITICAL_SECTION* section )
{
	return g_map_data.RtlTryEnterCriticalSection( section );
}

bool RtlLeaveCriticalSection( RTL_CRITICAL_SECTION* section )
{
	return NT_SUCCESS( g_map_data.RtlLeaveCriticalSection( section ) );
}

bool RtlDeleteCriticalSection( RTL_CRITICAL_SECTION* section )
{
	return NT_SUCCESS( g_map_data.RtlDeleteCriticalSection( section ) );
}

void RtlInitializeConditionVariable( RTL_CONDITION_VARIABLE* cv )
{
	return g_map_data.RtlInitializeConditionVariable( cv );
}

bool RtlSleepConditionVariableCS( RTL_CONDITION_VARIABLE* cv, RTL_CRITICAL_SECTION* section, LARGE_INTEGER* time )
{
	return NT_SUCCESS( g_map_data.RtlSleepConditionVariableCS( cv, section, time ) );
}

void RtlWakeConditionVariable( RTL_CONDITION_VARIABLE* cv )
{
	return g_map_data.RtlWakeConditionVariable( cv );
}

void RtlWakeAllConditionVariable( RTL_CONDITION_VARIABLE* cv )
{
	return g_map_data.RtlWakeAllConditionVariable( cv );
}

} // namespace horizon::win32