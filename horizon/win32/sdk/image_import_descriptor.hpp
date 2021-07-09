#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct IMAGE_IMPORT_DESCRIPTOR
{
	union
	{
		std::uint32_t Characteristics = 0;	// 0x0000
		std::uint32_t OriginalFirstThunk;		// 0x0000
	};
	std::uint32_t TimeDateStamp = 0;			// 0x0004
	std::uint32_t ForwarderChain = 0;			// 0x0008
	std::uint32_t Name = 0;								// 0x000C
	std::uint32_t FirstThunk = 0;					// 0x0010
};
// sizeof( IMAGE_IMPORT_DESCRIPTOR ) = 0x0014

} // namespace horizon::win32