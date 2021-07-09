#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

namespace horizon::vcruntime
{

// 
// [ class ]
// 
class SecurityCookie;

// 
// [ class ] implementation
// 
class SecurityCookie
{
public:
	SecurityCookie() noexcept;

public:
	bool Initialize() noexcept;
	void Uninitialize() noexcept;

public:
	void SetCookie( std::uintptr_t cookie ) noexcept;
	void SetCookieComplement( std::uintptr_t cookie_complement ) noexcept;

	std::uintptr_t GetCookie() const noexcept;
	std::uintptr_t GetCookieComplement() const noexcept;

protected:
	std::uintptr_t ComputeCookie() const noexcept;

protected:
	std::uintptr_t* m_cookie = nullptr;
	std::uintptr_t* m_cookie_complement = nullptr;
};

}

extern horizon::vcruntime::SecurityCookie* g_security_cookie;