#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

#pragma pack( push, 2 )

struct IMAGE_RELOCATION
{
	union
	{
		std::uint32_t VirtualAddress = 0;	// 0x0000
		std::uint32_t RelocCount;					// 0x0000
	};
	std::uint32_t SymbolTableIndex = 0;	// 0x0004
	std::uint16_t Type = 0;							// 0x0008
};
// sizeof( IMAGE_RELOCATION ) = 0x000A

#pragma pack( pop )

} // namespace horizon::win32