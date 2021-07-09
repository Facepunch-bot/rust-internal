#include "../rust/core.hpp"

namespace atom
{

void ImageLoad( void* instance, void* reserved )
{
	__try
	{
		// 
		// reset image headers
		// 
		std::memset( instance, 0, PAGE_SIZE );

		if( rust::Create() )
		{

		}
		else
		{
			TRACE( "%s: rust::Create() error!", ATOM_FUNCTION );
		}
	}
	__except( EXCEPTION_EXECUTE_HANDLER )
	{
		TRACE( "%s: Exception occured = '0x%08X'!", ATOM_FUNCTION, GetExceptionCode() );
	}
}

void ImageFree( void* reserved )
{
	if( reserved )
	{
		rust::Destroy();
	}
}

int Dispatch( void* instance, std::uint32_t reason, void* reserved )
{
	switch( reason )
	{
		case DLL_PROCESS_ATTACH:
		{
			ImageLoad( instance, reserved );
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			ImageFree( reserved );
			break;
		}
	}

	return TRUE;
}

} // namespace atom

int API_STDCALL DllMain( void* instance, unsigned long reason, void* reserved )
{
	return atom::Dispatch( instance, reason, reserved );
}