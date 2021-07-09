#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct XSTATE_FEATURE
{
	std::uint32_t Offset = 0;	// 0x0000
	std::uint32_t Size = 0;		// 0x0004
};
// sizeof( XSTATE_FEATURE ) = 0x0008

} // namespace horizon::win32