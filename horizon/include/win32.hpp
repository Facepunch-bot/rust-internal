#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _NO_CRT_STDIO_INLINE
#define _NO_CRT_STDIO_INLINE
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winternl.h>
#include <winioctl.h>

#pragma warning( push )
#pragma warning( disable : 4005 )
#include <ntstatus.h>

// #include <xnamath.h>

#include <d3d.h>
#include <d3d11.h>
#pragma warning( pop )
// #include <d3dx11.h>

#undef LOBYTE
#undef HIBYTE
#undef LOWORD
#undef HIWORD
#undef LODWORD
#undef HIDWORD

#undef BYTE1
#undef BYTE2
#undef WORD1
#undef WORD2

#define BYTE_ELEMENT( Data, Index )		( *( ( BYTE* )&( Data ) + Index ) )
#define WORD_ELEMENT( Data, Index )		( *( ( WORD* )&( Data ) + Index ) )
#define DWORD_ELEMENT( Data, Index )	( *( ( DWORD* )&( Data ) + Index ) )

#define LOBYTE( Data )					BYTE_ELEMENT( Data, 0 )
#define HIBYTE( Data )					BYTE_ELEMENT( Data, 1 )

#define LOWORD( Data )					WORD_ELEMENT( Data, 0 )
#define HIWORD( Data )					WORD_ELEMENT( Data, 1 )

#define LODWORD( Data )					DWORD_ELEMENT( Data, 0 )
#define HIDWORD( Data )					DWORD_ELEMENT( Data, 1 )

#define BYTE1( Data )					BYTE_ELEMENT( Data, 1 )
#define BYTE2( Data )					BYTE_ELEMENT( Data, 2 )

#define WORD1( Data )					WORD_ELEMENT( Data, 1 )
#define WORD2( Data )					WORD_ELEMENT( Data, 2 )

#define DWORD1( Data )					DWORD_ELEMENT( Data, 1 )
#define DWORD2( Data )					DWORD_ELEMENT( Data, 2 )
