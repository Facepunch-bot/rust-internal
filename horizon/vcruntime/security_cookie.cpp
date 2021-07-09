#include "security_cookie.hpp"

#include "../core/map_data.hpp"

#include "../win32/trace.hpp"
#include "../win32/process.hpp"
#include "../win32/time.hpp"

using namespace horizon;

#if defined( HORIZON_X86 )
	#define DEFAULT_SECURITY_COOKIE		( static_cast< std::uintptr_t >( 0xBB40E64E ) )
#elif defined( HORIZON_X64 )
	#define DEFAULT_SECURITY_COOKIE		( static_cast< std::uintptr_t >( 0x00002B992DDFA232 ) )
#endif // HORIZON_X86

vcruntime::SecurityCookie* g_security_cookie = nullptr;

extern "C"
{
	std::uintptr_t __security_cookie = DEFAULT_SECURITY_COOKIE;
	std::uintptr_t __security_cookie_complement = ~DEFAULT_SECURITY_COOKIE;
}; // extern "C"

union FT
{
	std::uint64_t value = 0;
	FILETIME data;
};
// sizeof( FT ) = 0x0008

namespace horizon::vcruntime
{

// 
// [ SecurityCookie ] implementation
// 
SecurityCookie::SecurityCookie() noexcept
	: m_cookie( nullptr )
	, m_cookie_complement( nullptr )
{ }

bool SecurityCookie::Initialize() noexcept
{
	m_cookie = std::addressof( __security_cookie );

	if( !m_cookie )
	{
		TRACE( "%s: m_cookie is nullptr!", ATOM_FUNCTION );
		return false;
	}

	m_cookie_complement = std::addressof( __security_cookie_complement );

	if( !m_cookie_complement )
	{
		TRACE( "%s: m_cookie_complement is nullptr!", ATOM_FUNCTION );
		return false;
	}

	SetCookie( DEFAULT_SECURITY_COOKIE );
	SetCookieComplement( ~DEFAULT_SECURITY_COOKIE );

	auto cookie = GetCookie();

	if( ( cookie != DEFAULT_SECURITY_COOKIE )
#if defined( HORIZON_X86 )
		&& ( cookie & 0xFFFF0000 ) != 0
#endif
		)
	{
		SetCookieComplement( ~cookie );
		return true;
	}

	cookie = ComputeCookie();

	if( cookie == DEFAULT_SECURITY_COOKIE )
	{
		cookie = DEFAULT_SECURITY_COOKIE + 1;
	}
#if defined( HORIZON_X86 )
	else if( ( cookie & 0xFFFF0000 ) == 0 )
	{
		cookie |= ( ( cookie | 0x4711 ) << 16 );
	}
#endif // HORIZON_X86

	SetCookie( cookie );
	SetCookieComplement( ~cookie );

	return true;
}

void SecurityCookie::SetCookie( std::uintptr_t cookie ) noexcept
{
	*m_cookie = cookie;
}

void SecurityCookie::SetCookieComplement( std::uintptr_t cookie_complement ) noexcept
{
	*m_cookie_complement = cookie_complement;
}

std::uintptr_t SecurityCookie::GetCookie() const noexcept
{
	return *m_cookie;
}

std::uintptr_t SecurityCookie::GetCookieComplement() const noexcept
{
	return *m_cookie_complement;
}

void SecurityCookie::Uninitialize() noexcept
{ }

std::uintptr_t SecurityCookie::ComputeCookie() const noexcept
{
	FT system_time = { };
	win32::GetSystemTimeAsFileTime( &system_time.data );

#if defined( HORIZON_X86 )
	auto cookie = system_time.data.dwLowDateTime;
	cookie ^= system_time.data.dwHighDateTime;
#elif defined( HORIZON_X64 )
	auto cookie = system_time.value;
#endif // HORIZON_X86

	cookie ^= win32::NtCurrentProcessId();
	cookie ^= win32::NtCurrentThreadId();

#if defined( HORIZON_X86 )
	cookie ^= static_cast< std::uintptr_t >( win32::GetTickCount64() );
#elif defined( HORIZON_X64 )
	cookie ^= win32::GetTickCount64() << 56;
	cookie ^= win32::GetTickCount64();
#endif // HORIZON_X86

	win32::LARGE_INTEGER performance_counter = { };

	if( !g_map_data.RtlQueryPerformanceCounter( &performance_counter ) )
	{
		TRACE( "%s: win32::QueryPerformanceCounter( ... ) error! (0x%08X)", ATOM_FUNCTION, win32::GetLastError() );
	}

#if defined( HORIZON_X86 )
	cookie ^= performance_counter.LowPart;
	cookie ^= static_cast< std::uintptr_t >( performance_counter.HighPart );
#elif defined( HORIZON_X64 )
	cookie ^= ( ( static_cast< std::uintptr_t >( performance_counter.LowPart ) << 32 ) ^ static_cast< std::uintptr_t >( performance_counter.HighPart ) );
	cookie &= 0xFFFFFFFFFFFF;
#endif // HORIZON_X86

	return cookie;
}

}

#pragma warning( push )
#pragma warning( disable : 28251 )

extern "C"
{

	void __security_check_cookie( std::uintptr_t )
	{ }

	void __chkstk()
	{ }

	void __GSHandlerCheck()
	{ }

}; // extern "C"

#pragma warning( pop )