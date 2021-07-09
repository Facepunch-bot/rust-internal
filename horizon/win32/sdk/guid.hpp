#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct GUID
{
	std::uint32_t Data1 = 0;				// 0x0000
	std::uint16_t Data2 = 0;				// 0x0004
	std::uint16_t Data3 = 0;				// 0x0006
	std::uint8_t Data4[ 8 ] = { };	// 0x0008
};
// sizeof( GUID ) = 0x0010

} // namespace horizon::win32