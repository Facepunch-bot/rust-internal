#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct STRING32
{
	std::uint16_t Length = 0;
	std::uint16_t MaximumLength = 0;
	std::uint32_t Buffer = 0;
};

struct STRING64
{
	std::uint16_t Length = 0;
	std::uint16_t MaximumLength = 0;
	FIELD_PAD( 0x0004 );
	std::uint64_t Buffer = 0;
};

struct STRING
{
	std::uint16_t Length = 0;
	std::uint16_t MaximumLength = 0;
	FIELD_PAD( 0x0004 );
	char* Buffer = nullptr;
};

using ANSI_STRING32 = STRING32;
using ANSI_STRING64 = STRING64;
using ANSI_STRING = STRING;

} // namespace horizon::win32