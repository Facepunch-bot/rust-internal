#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "large_integer.hpp"

namespace horizon::win32
{

struct SECTION_BASIC_INFORMATION
{
	void* BaseAddress = nullptr;						// 0x0000
	std::uint32_t AllocationAttributes = 0;	// 0x0008
	FIELD_PAD( 0x0004 );										// 0x000C
	LARGE_INTEGER MaximumSize = { };				// 0x0010
};
// sizeof( SECTION_BASIC_INFORMATION ) = 0x0018

} // namespace horizon::win32