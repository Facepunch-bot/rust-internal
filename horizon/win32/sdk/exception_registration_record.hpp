#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct EXCEPTION_REGISTRATION_RECORD32
{
	std::uint32_t Next = 0;
	std::uint32_t Handler = 0;
};

struct EXCEPTION_REGISTRATION_RECORD64
{
	std::uint64_t Next = 0;
	std::uint64_t Handler = 0;
};

struct EXCEPTION_REGISTRATION_RECORD
{
	EXCEPTION_REGISTRATION_RECORD* Next = nullptr;
	void* Handler = nullptr;
};

} // namespace horizon::win32