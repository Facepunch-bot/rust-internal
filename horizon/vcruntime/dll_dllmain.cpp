#include "dll_dllmain.hpp"
#include "security_cookie.hpp"
#include "thread_safe_statics.hpp"
#include "initializers.hpp"

#include "../core/map_data.hpp"

#include "../win32/trace.hpp"
#include "../win32/image.hpp"
#include "../win32/process.hpp"

namespace horizon::vcruntime
{

bool DllMainCRTProcessAttach( void* instance, void* reserved )
{
	return true;
}

bool DllMainCRTProcessDetach( void* reserved )
{
	return true;
}

bool DllMainCRTDispatch( void* instance, std::uint32_t reason, void* reserved )
{
	switch( reason )
	{
		case DLL_PROCESS_ATTACH:
		{
			return DllMainCRTProcessAttach( instance, reserved );
		}
		case DLL_PROCESS_DETACH:
		{
			return DllMainCRTProcessDetach( reserved );
		}
	}

	return true;
}

int DllMainDispatch( void* instance, std::uint32_t reason, void* reserved )
{
	return DllMain( instance, reason, reserved );
}

bool InitializeMapData( core::MapData* map_data )
{
	if( memory::IsAddressValid( map_data ) )
	{
		if( map_data->IsValid() )
		{
			if( map_data->Create() )
			{
				std::memcpy( &g_map_data, map_data, sizeof( core::MapData ) );
				return true;
			}
		}
	}

	return false;
}

void UninitializeMapData()
{
	std::memset( &g_map_data, 0, sizeof( g_map_data ) );
}

bool InitializeExceptionSupport( std::uintptr_t image )
{
	const auto image_data_directory = win32::GetImageDataDirectory( image, win32::ImageDirectoryEntryException );

	if( memory::IsAddressValid( image_data_directory ) )
	{
		const auto function_table = reinterpret_cast< win32::IMAGE_RUNTIME_FUNCTION_ENTRY* >( image + image_data_directory->VirtualAddress );
		const auto entry_count = static_cast< std::uint32_t >( image_data_directory->Size / sizeof( win32::IMAGE_RUNTIME_FUNCTION_ENTRY ) );

		if( g_map_data.RtlAddFunctionTable( function_table, entry_count, image ) )
		{
			return true;
		}
		else
		{
			TRACE( "%s: RtlAddFunctionTable( '0x%016llX', '0x%08X', '0x%016llX' ) error!", FN, memory::ToAddress( function_table ), entry_count, image );
		}
	}
	else
	{
		TRACE( "%s: win32::GetImageDataDirectory( '0x%016llX', '0x%02X' ) error!", FN, image, win32::ImageDirectoryEntryException );
	}

	return false;
}

void UninitializeExceptionSupport()
{
	const auto image = g_map_data.m_base;
	const auto image_data_directory = win32::GetImageDataDirectory( image, win32::ImageDirectoryEntryException );

	if( memory::IsAddressValid( image_data_directory ) )
	{
		const auto function_table = reinterpret_cast< win32::IMAGE_RUNTIME_FUNCTION_ENTRY* >( image + image_data_directory->VirtualAddress );
		const auto entry_count = static_cast< std::uint32_t >( image_data_directory->Size / sizeof( win32::IMAGE_RUNTIME_FUNCTION_ENTRY ) );

		if( !g_map_data.RtlDeleteFunctionTable( function_table ) )
		{
			TRACE( "%s: RtlDeleteFunctionTable( '0x%016llX' ) error!", FN, memory::ToAddress( function_table ) );
		}
	}
	else
	{
		TRACE( "%s: win32::GetImageDataDirectory( '0x%016llX', '0x%02X' ) error!", FN, image, win32::ImageDirectoryEntryException );
	}
}

bool InitializeRuntimeData()
{
	__try
	{
		g_security_cookie = new SecurityCookie();
		g_thread_safe_statics = new ThreadSafeStatics();

		if( memory::IsAddressValid( g_security_cookie ) &&
				memory::IsAddressValid( g_thread_safe_statics ) )
		{
			return ( g_security_cookie->Initialize() &&
							 g_thread_safe_statics->Initialize() );
		}
		else
		{
			TRACE( "%s: Runtime data allocation error!", FN );
		}
	}
	__except( EXCEPTION_EXECUTE_HANDLER )
	{
		TRACE( "%s: Exception occured = '0x%08X'!", FN, GetExceptionCode() );
	}

	return false;
}

void UninitializeRuntimeData()
{
	__try
	{
		if( memory::IsAddressValid( g_thread_safe_statics ) )
		{
			g_thread_safe_statics->Uninitialize();
		}

		if( memory::IsAddressValid( g_security_cookie ) )
		{
			g_security_cookie->Uninitialize();
		}

		memory::SafeDelete( g_thread_safe_statics );
		memory::SafeDelete( g_security_cookie );
	}
	__except( EXCEPTION_EXECUTE_HANDLER )
	{
		TRACE( "%s: Exception occured = '0x%08X'!", FN, GetExceptionCode() );
	}
}

bool InitializeImageInstance( void* instance, void* reserved )
{
	const auto map_data = static_cast< core::MapData* >( reserved );

	if( InitializeMapData( map_data ) )
	{
		win32::LARGE_INTEGER time = { };
		win32::RtlQueryPerformanceCounter( &time );

		// g_map_data.OutputDebugStringA( SECURE( "win32::RtlQueryPerformanceCounter()" ) );

		// char output[ 1024 ] = { };
		// win32::sprintf_s( output, ARRAYSIZE( output ), SECURE( "[horizon] time.QuadPart = '%lld'" ), time.QuadPart );
		// g_map_data.OutputDebugStringA( output );

		// TRACE( "time.QuadPart = '%lld'", time.QuadPart );
		// TRACE( "g_map_data.m_time.QuadPart = '%lld'", g_map_data.m_time.QuadPart );

		const auto code = crt_init();

		if( code == 0 )
		{
			const auto image = memory::ToAddress( instance );

			if( InitializeExceptionSupport( image ) )
			{
				if( InitializeRuntimeData() )
				{
					return true;
				}
				else
				{
					TRACE( "%s: InitializeRuntimeData() error!", ATOM_FUNCTION );
				}
			}
			else
			{
				TRACE( "%s: InitializeExceptionSupport( '0x%016llX' ) error!", ATOM_FUNCTION, image );
			}
		}
	}

	return false;
}

void UninitializeImageInstance( void* reserved )
{
	atom::vcruntime::ExecuteTerminators();

	UninitializeRuntimeData();
	UninitializeExceptionSupport();
	UninitializeMapData();
}

} // namespace horizon::vcruntime

extern "C"
{

	BOOL API_STDCALL _CRT_INIT( void* instance, unsigned long reason, void* reserved )
	{
		return horizon::vcruntime::DllMainDispatch( instance, reason, reserved );
	}

	BOOL API_STDCALL _DllMainCRTStartup( void* instance, unsigned long reason, void* reserved )
	{
		if( reason == DLL_PROCESS_ATTACH )
		{
			horizon::vcruntime::InitializeImageInstance( instance, reserved );
		}

		const auto result = horizon::vcruntime::DllMainDispatch( instance, reason, reserved );

		if( reason == DLL_PROCESS_DETACH )
		{
			horizon::vcruntime::UninitializeImageInstance( reserved );
		}

		return result;
	}

} // extern "C"