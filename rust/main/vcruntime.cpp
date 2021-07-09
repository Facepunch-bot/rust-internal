#include "../unity/sdk.hpp"

#pragma comment( linker, "/merge:.CRT=.rdata" )
#pragma comment( linker, "/merge:.pdata=.rdata" )
#pragma comment( linker, "/merge:.rdata=.text" )

extern "C"
{

	std::int32_t _fltused = 0x9875;

}; // extern "C"

using _PVFV = void( * )( );

extern "C"
{

	// 
	// std::unordered_map support
	// 
#pragma function( ceilf )
	float ceilf( float x )
	{
		return horizon::win32::ceil( x );
	}

	int _purecall()
	{
		return 0;
	}

}; // extern "C"

type_info::~type_info()
{ }

__declspec( noreturn ) void _invalid_parameter_noinfo_noreturn()
{ }

void __std_exception_copy( struct __std_exception_data const*, struct __std_exception_data* )
{ }

void __std_exception_destroy( struct __std_exception_data* )
{ }

namespace std
{

void _Xlength_error( const char* )
{ }

void _Xout_of_range( const char* )
{ }

} // namespace std

extern "C"
{

	EXCEPTION_DISPOSITION __C_specific_handler( PEXCEPTION_RECORD ExceptionRecord, PVOID EstablisherFrame, PCONTEXT ContextRecord, PDISPATCHER_CONTEXT DispatcherContext )
	{
		return g_map_data.__C_specific_handler( ExceptionRecord, EstablisherFrame, ContextRecord, DispatcherContext );
	}

	void _CxxThrowException( void*, _ThrowInfo* )
	{ }

	void __CxxFrameHandler4()
	{ }

}; // extern "C"