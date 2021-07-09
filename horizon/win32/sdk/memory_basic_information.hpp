#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct MEMORY_BASIC_INFORMATION
{
	void* BaseAddress = nullptr;					// 0x0000
	void* AllocationBase = nullptr;				// 0x0008
	std::uint32_t AllocationProtect = 0;	// 0x0010
	FIELD_PAD( 0x0004 );									// 0x0014
	std::size_t RegionSize = 0;						// 0x0018
	std::uint32_t State = 0;							// 0x0020
	std::uint32_t Protect = 0;						// 0x0024
	std::uint32_t Type = 0;								// 0x0028
	FIELD_PAD( 0x0004 );									// 0x002C
};
// sizeof( MEMORY_BASIC_INFORMATION ) = 0x0030

} // namespace horizon::win32