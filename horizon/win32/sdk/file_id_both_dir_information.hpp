#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "large_integer.hpp"

namespace horizon::win32
{

struct FILE_ID_BOTH_DIR_INFORMATION
{
	std::uint32_t NextEntryOffset = 0;	// 0x0000
	std::uint32_t FileIndex = 0;				// 0x0004
	LARGE_INTEGER CreationTime = { };		// 0x0008
	LARGE_INTEGER LastAccessTime = { };	// 0x0010
	LARGE_INTEGER LastWriteTime = { };	// 0x0018
	LARGE_INTEGER ChangeTime = { };			// 0x0020
	LARGE_INTEGER EndOfFile = { };			// 0x0028
	LARGE_INTEGER AllocationSize = { };	// 0x0030
	std::uint32_t FileAttributes = 0;		// 0x0038
	std::uint32_t FileNameLength = 0;		// 0x003C
	std::uint32_t EaSize = 0;						// 0x0040
	char ShortNameLength = 0;						// 0x0044
	FIELD_PAD( 0x0001 );								// 0x0045
	wchar_t ShortName[ 12 ] = { };			// 0x0046
	FIELD_PAD( 0x0002 );								// 0x005E
	LARGE_INTEGER FileId = { };					// 0x0060
	wchar_t FileName[ 1 ] = { };				// 0x0068
};
// sizeof( FILE_ID_BOTH_DIR_INFORMATION ) = 0x0070

} // namespace horizon::win32