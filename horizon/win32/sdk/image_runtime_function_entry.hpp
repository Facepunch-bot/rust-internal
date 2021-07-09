#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct IMAGE_RUNTIME_FUNCTION_ENTRY
{
	std::uint32_t BeginAddress = 0;					// 0x0000
	std::uint32_t EndAddress = 0;						// 0x0004
	union
	{
		std::uint32_t UnwindInfoAddress = 0;	// 0x0008
		std::uint32_t UnwindData;							// 0x0008
	};
};
// sizeof( IMAGE_RUNTIME_FUNCTION_ENTRY ) = 0x000C

} // namespace horizon::win32