#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct KSYSTEM_TIME
{
	std::uint32_t LowPart = 0;	// 0x0000
	std::int32_t High1Time = 0;	// 0x0004
	std::int32_t High2Time = 0;	// 0x0008
};
// sizeof( KSYSTEM_TIME ) = 0x000C

} // namespace horizon::win32