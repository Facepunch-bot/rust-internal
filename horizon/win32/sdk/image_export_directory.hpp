#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct IMAGE_EXPORT_DIRECTORY
{
	std::uint32_t Characteristics = 0;				// 0x0000
	std::uint32_t TimeDateStamp = 0;					// 0x0004
	std::uint16_t MajorVersion = 0;						// 0x0008
	std::uint16_t MinorVersion = 0;						// 0x000A
	std::uint32_t Name = 0;										// 0x000C
	std::uint32_t Base = 0;										// 0x0010
	std::uint32_t NumberOfFunctions = 0;			// 0x0014
	std::uint32_t NumberOfNames = 0;					// 0x0018
	std::uint32_t AddressOfFunctions = 0;			// 0x001C
	std::uint32_t AddressOfNames = 0;					// 0x0020
	std::uint32_t AddressOfNameOrdinals = 0;	// 0x0024
};
// sizeof( IMAGE_EXPORT_DIRECTORY ) = 0x0028

} // namespace horizon::win32