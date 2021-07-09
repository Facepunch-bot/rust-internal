#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

constexpr std::size_t ImageSizeOfFileHeader = 20;

constexpr std::uint16_t ImageFileRelocsStripped = 0x0001;
constexpr std::uint16_t ImageFileExecutableImage = 0x0002;
constexpr std::uint16_t ImageFileLineNumsStripped = 0x0004;
constexpr std::uint16_t ImageFileLocalSymsStripped = 0x0008;
constexpr std::uint16_t ImageFileAggresiveWsTrim = 0x0010;
constexpr std::uint16_t ImageFileLargeAddressAware = 0x0020;
constexpr std::uint16_t ImageFileBytesReversedLo = 0x0080;
constexpr std::uint16_t ImageFile32BitMachine = 0x0100;
constexpr std::uint16_t ImageFileDebugStripped = 0x0200;
constexpr std::uint16_t ImageFileRemovableRunFromSwap = 0x0400;
constexpr std::uint16_t ImageFileNetRunFromSwap = 0x0800;
constexpr std::uint16_t ImageFileSystem = 0x1000;
constexpr std::uint16_t ImageFileDll = 0x2000;
constexpr std::uint16_t ImageFileUpSystemOnly = 0x4000;
constexpr std::uint16_t ImageFileBytesReversedHi = 0x8000;

constexpr std::uint16_t ImageFileMachineUnknown = 0x0000;
constexpr std::uint16_t ImageFileMachineTargetHost = 0x0001;
constexpr std::uint16_t ImageFileMachineI386 = 0x014C;
constexpr std::uint16_t ImageFileMachineIA64 = 0x0200;
constexpr std::uint16_t ImageFileMachineAMD64 = 0x8664;

struct IMAGE_FILE_HEADER
{
	std::uint16_t Machine = 0;							// 0x0000
	std::uint16_t NumberOfSections = 0;			// 0x0002
	std::uint32_t TimeDateStamp = 0;				// 0x0004
	std::uint32_t PointerToSymbolTable = 0;	// 0x0008
	std::uint32_t NumberOfSymbols = 0;			// 0x000C
	std::uint16_t SizeOfOptionalHeader = 0;	// 0x0010
	std::uint16_t Characteristics = 0;			// 0x0012
};
// sizeof( IMAGE_FILE_HEADER ) = 0x0014

} // namespace horizon::win32