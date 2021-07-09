#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct IMAGE_BASE_RELOCATION
{
	std::uint32_t VirtualAddress = 0;	// 0x0000
	std::uint32_t SizeOfBlock = 0;		// 0x0004
};
// sizeof( IMAGE_BASE_RELOCATION ) = 0x0008

} // namespace horizon::win32