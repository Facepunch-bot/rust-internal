#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "large_integer.hpp"

namespace horizon::win32
{

struct FILE_DIRECTORY_INFORMATION
{
	std::uint32_t NextEntryOffset = 0;
	std::uint32_t FileIndex = 0;
	LARGE_INTEGER CreationTime = { };
	LARGE_INTEGER LastAccessTime = { };
	LARGE_INTEGER LastWriteTime = { };
	LARGE_INTEGER ChangeTime = { };
	LARGE_INTEGER EndOfFile = { };
	LARGE_INTEGER AllocationSize = { };
	std::uint32_t FileAttributes = 0;
	std::uint32_t FileNameLength = 0;
	wchar_t FileName[ MAX_PATH ] = { };
};
// sizeof( FILE_DIRECTORY_INFORMATION ) = 0x0248

} // namespace horizon::win32