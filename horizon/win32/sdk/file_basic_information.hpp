#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "large_integer.hpp"

namespace horizon::win32
{

struct FILE_BASIC_INFORMATION
{
	LARGE_INTEGER CreationTime = { };		// 0x0000
	LARGE_INTEGER LastAccessTime = { };	// 0x0008
	LARGE_INTEGER LastWriteTime = { };	// 0x0010
	LARGE_INTEGER ChangeTime = { };			// 0x0018
	std::uint32_t FileAttributes = 0;		// 0x0020
	FIELD_PAD( 0x0004 );								// 0x0024
};
// sizeof( FILE_BASIC_INFORMATION ) = 0x0028

} // namespace horizon::win32