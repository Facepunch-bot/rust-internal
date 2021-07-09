#pragma once

#if defined( _M_IX86 )
	#define HORIZON_X86
#elif defined( _M_X64 )
	#define HORIZON_X64
#else
	#error "Not supported architecture!"
#endif // _M_IX86

#if defined( _DEBUG )
	#define HORIZON_DEBUG
#elif defined( NDEBUG )
	#define HORIZON_RELEASE
#else
	#error "Not supported configuration!"
#endif // _DEBUG

#define API_CDECL										__cdecl
#define API_STDCALL									__stdcall
#define API_THISCALL								__thiscall
#define API_FASTCALL								__fastcall
#define API_VECTORCALL							__vectorcall

#define API_NT											API_STDCALL
#define API_WIN32										API_STDCALL
#define API_D3D											API_STDCALL

#define JOIN_IMPL( A, B )						A ## B
#define JOIN( A, B )								JOIN_IMPL( A, B )

#define FIELD_PAD( Size )						std::uint8_t JOIN( __pad, __COUNTER__ )[ Size ] = { }

#define ATOM_THREAD									__declspec( thread )
#define ATOM_ALLOCATE( Section )		__declspec( allocate( Section ) )

#define FUNCTION										SECURE( __FUNCTION__ )
#define FN													SECURE( __FUNCTION__ )

#define ATOM_FUNCTION								SECURE( __FUNCTION__ )