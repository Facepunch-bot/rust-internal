#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "large_integer.hpp"

namespace horizon::win32
{

struct FILE_STANDARD_INFORMATION
{
	LARGE_INTEGER AllocationSize = { };	// 0x0000
	LARGE_INTEGER EndOfFile = { };			// 0x0008
	std::uint32_t NumberOfLinks = 0;		// 0x0010
	std::uint8_t DeletePending = 0;			// 0x0014
	std::uint8_t Directory = 0;					// 0x0015
	FIELD_PAD( 0x0002 );								// 0x0016
};
// sizeof( FILE_STANDARD_INFORMATION ) = 0x0018

} // namespace horizon::win32