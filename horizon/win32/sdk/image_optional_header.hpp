#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "image_data_directory.hpp"

namespace horizon::win32
{

constexpr std::uint16_t ImageNtOptionalHdr32Magic = 0x010B;
constexpr std::uint16_t ImageNtOptionalHdr64Magic = 0x020B;

struct IMAGE_OPTIONAL_HEADER32
{
	std::uint16_t Magic = 0;																										// 0x0000
	std::uint8_t MajorLinkerVersion = 0;																				// 0x0002
	std::uint8_t MinorLinkerVersion = 0;																				// 0x0003
	std::uint32_t SizeOfCode = 0;																								// 0x0004
	std::uint32_t SizeOfInitializedData = 0;																		// 0x0008
	std::uint32_t SizeOfUninitializedData = 0;																	// 0x000C
	std::uint32_t AddressOfEntryPoint = 0;																			// 0x0010
	std::uint32_t BaseOfCode = 0;																								// 0x0014
	std::uint32_t BaseOfData = 0;																								// 0x0018
	std::uint32_t ImageBase = 0;																								// 0x001C
	std::uint32_t SectionAlignment = 0;																					// 0x0020
	std::uint32_t FileAlignment = 0;																						// 0x0024
	std::uint16_t MajorOperatingSystemVersion = 0;															// 0x0028
	std::uint16_t MinorOperatingSystemVersion = 0;															// 0x002A
	std::uint16_t MajorImageVersion = 0;																				// 0x002C
	std::uint16_t MinorImageVersion = 0;																				// 0x002E
	std::uint16_t MajorSubsystemVersion = 0;																		// 0x0030
	std::uint16_t MinorSubsystemVersion = 0;																		// 0x0032
	std::uint32_t Win32VersionValue = 0;																				// 0x0034
	std::uint32_t SizeOfImage = 0;																							// 0x0038
	std::uint32_t SizeOfHeaders = 0;																						// 0x003C
	std::uint32_t CheckSum = 0;																									// 0x0040
	std::uint16_t Subsystem = 0;																								// 0x0044
	std::uint16_t DllCharacteristics = 0;																				// 0x0046
	std::uint32_t SizeOfStackReserve = 0;																				// 0x0048
	std::uint32_t SizeOfStackCommit = 0;																				// 0x004C
	std::uint32_t SizeOfHeapReserve = 0;																				// 0x0050
	std::uint32_t SizeOfHeapCommit = 0;																					// 0x0054
	std::uint32_t LoaderFlags = 0;																							// 0x0058
	std::uint32_t NumberOfRvaAndSizes = 0;																			// 0x005C
	IMAGE_DATA_DIRECTORY DataDirectory[ ImageNumberOfDirectoryEntries ] = { };	// 0x0060
};
// sizeof( IMAGE_OPTIONAL_HEADER32 ) = 0x00E0

struct IMAGE_OPTIONAL_HEADER64
{
	std::uint16_t Magic = 0;																										// 0x0000
	std::uint8_t MajorLinkerVersion = 0;																				// 0x0002
	std::uint8_t MinorLinkerVersion = 0;																				// 0x0003
	std::uint32_t SizeOfCode = 0;																								// 0x0004
	std::uint32_t SizeOfInitializedData = 0;																		// 0x0008
	std::uint32_t SizeOfUninitializedData = 0;																	// 0x000C
	std::uint32_t AddressOfEntryPoint = 0;																			// 0x0010
	std::uint32_t BaseOfCode = 0;																								// 0x0014
	std::uint64_t ImageBase = 0;																								// 0x0018
	std::uint32_t SectionAlignment = 0;																					// 0x0020
	std::uint32_t FileAlignment = 0;																						// 0x0024
	std::uint16_t MajorOperatingSystemVersion = 0;															// 0x0028
	std::uint16_t MinorOperatingSystemVersion = 0;															// 0x002A
	std::uint16_t MajorImageVersion = 0;																				// 0x002C
	std::uint16_t MinorImageVersion = 0;																				// 0x002E
	std::uint16_t MajorSubsystemVersion = 0;																		// 0x0030
	std::uint16_t MinorSubsystemVersion = 0;																		// 0x0032
	std::uint32_t Win32VersionValue = 0;																				// 0x0034
	std::uint32_t SizeOfImage = 0;																							// 0x0038
	std::uint32_t SizeOfHeaders = 0;																						// 0x003C
	std::uint32_t CheckSum = 0;																									// 0x0040
	std::uint16_t Subsystem = 0;																								// 0x0044
	std::uint16_t DllCharacteristics = 0;																				// 0x0046
	std::uint64_t SizeOfStackReserve = 0;																				// 0x0048
	std::uint64_t SizeOfStackCommit = 0;																				// 0x0050
	std::uint64_t SizeOfHeapReserve = 0;																				// 0x0058
	std::uint64_t SizeOfHeapCommit = 0;																					// 0x0060
	std::uint32_t LoaderFlags = 0;																							// 0x0068
	std::uint32_t NumberOfRvaAndSizes = 0;																			// 0x006C
	IMAGE_DATA_DIRECTORY DataDirectory[ ImageNumberOfDirectoryEntries ] = { };	// 0x0070
};
// sizeof( IMAGE_OPTIONAL_HEADER64 ) = 0x00F0

#if defined( HORIZON_X32 )
using IMAGE_OPTIONAL_HEADER = IMAGE_OPTIONAL_HEADER32;
#elif defined( HORIZON_X64 )
using IMAGE_OPTIONAL_HEADER = IMAGE_OPTIONAL_HEADER64;
#endif // HORIZON_X32

} // namespace horizon::win32