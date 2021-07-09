#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

constexpr std::uint16_t ImageSizeOfShortName = 8;
constexpr std::uint16_t ImageSizeOfSectionHeader = 40;


struct IMAGE_RELOCATION;

struct IMAGE_SECTION_HEADER
{
	std::uint8_t Name[ ImageSizeOfShortName ] = { };	// 0x0000
	union
	{
		std::uint32_t PhysicalAddress = 0;							// 0x0008
		std::uint32_t VirtualSize;											// 0x0008
	} Misc = { };																			// 0x0008
	std::uint32_t VirtualAddress = 0;									// 0x000C
	std::uint32_t SizeOfRawData = 0;									// 0x0010
	std::uint32_t PointerToRawData = 0;								// 0x0014
	std::uint32_t PointerToRelocations = 0;						// 0x0018
	std::uint32_t PointerToLinenumbers = 0;						// 0x001C
	std::uint16_t NumberOfRelocations = 0;						// 0x0020
	std::uint16_t NumberOfLinenumbers = 0;						// 0x0022
	std::uint32_t Characteristics = 0;								// 0x0024
};
// sizeof( IMAGE_SECTION_HEADER ) = 0x0028

} // namespace horizon::win32