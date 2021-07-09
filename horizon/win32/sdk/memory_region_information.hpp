#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "memory_working_set_block.hpp"

namespace horizon::win32
{

struct MEMORY_REGION_INFORMATION
{
	void* AllocationBase = 0;											// 0x0000
	std::uint32_t AllocationProtect = 0;					// 0x0008
	union
	{
		std::uint32_t RegionType = 0;								// 0x000C
		struct
		{
			std::uint32_t Private : 1;								// 0x000C
			std::uint32_t MappedDataFile : 1;					// 0x000C
			std::uint32_t MappedImage : 1;						// 0x000C
			std::uint32_t MappedPageFile : 1;					// 0x000C
			std::uint32_t MappedPhysical : 1;					// 0x000C
			std::uint32_t DirectMapped : 1;						// 0x000C
			std::uint32_t SoftwareEnclave : 1;				// 0x000C
			std::uint32_t PageSize64Kb : 1;						// 0x000C
			std::uint32_t PlaceholderReservation : 1;	// 0x000C
			std::uint32_t Reserved : 23;							// 0x000C
		};
	};
	std::size_t RegionSize = 0;										// 0x0010
	std::size_t CommitSize = 0;										// 0x0018
	std::uintptr_t PartitionId = 0;								// 0x0020
};
// sizeof( MEMORY_REGION_INFORMATION ) = 0x0028

} // namespace horizon::win32