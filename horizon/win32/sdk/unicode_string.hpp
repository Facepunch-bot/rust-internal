#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct UNICODE_STRING32
{
	std::uint16_t Length = 0;
	std::uint16_t MaximumLength = 0;
	std::uint32_t Buffer = 0;
};

struct UNICODE_STRING64
{
	std::uint16_t Length = 0;
	std::uint16_t MaximumLength = 0;
	FIELD_PAD( 0x0004 );
	std::uint64_t Buffer = 0;
};

struct UNICODE_STRING
{
	std::uint16_t Length = 0;
	std::uint16_t MaximumLength = 0;
	FIELD_PAD( 0x0004 );
	wchar_t* Buffer = nullptr;
};

} // namespace horizon::win32