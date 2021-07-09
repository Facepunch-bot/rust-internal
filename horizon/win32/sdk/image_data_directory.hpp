#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

constexpr std::uint16_t ImageDirectoryEntryExport = 0;
constexpr std::uint16_t ImageDirectoryEntryImport = 1;
constexpr std::uint16_t ImageDirectoryEntryResource = 2;
constexpr std::uint16_t ImageDirectoryEntryException = 3;
constexpr std::uint16_t ImageDirectoryEntrySecurity = 4;
constexpr std::uint16_t ImageDirectoryEntryBaseReloc = 5;
constexpr std::uint16_t ImageDirectoryEntryDebug = 6;
constexpr std::uint16_t ImageDirectoryEntryArchitecture = 7;
constexpr std::uint16_t ImageDirectoryEntryGlobalPtr = 8;
constexpr std::uint16_t ImageDirectoryEntryTLS = 9;
constexpr std::uint16_t ImageDirectoryEntryLoadConfig = 10;
constexpr std::uint16_t ImageDirectoryEntryBoundImport = 11;
constexpr std::uint16_t ImageDirectoryEntryIAT = 12;
constexpr std::uint16_t ImageDirectoryEntryDelayImport = 13;
constexpr std::uint16_t ImageDirectoryEntryComDescriptor = 14;

constexpr std::uint16_t ImageNumberOfDirectoryEntries = 16;

struct IMAGE_DATA_DIRECTORY
{
	std::uint32_t VirtualAddress = 0;	// 0x0000
	std::uint32_t Size = 0;						// 0x0004
};
// sizeof( IMAGE_DATA_DIRECTORY ) = 0x0008

} // namespace horizon::win32