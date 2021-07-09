#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "memory_working_set_block.hpp"

namespace horizon::win32
{

struct MEMORY_WORKING_SET_INFORMATION
{
	std::size_t NumberOfEntries = 0;										// 0x0000
	MEMORY_WORKING_SET_BLOCK WorkingSetInfo[ 1 ] = { };	// 0x0008
};
// sizeof( MEMORY_WORKING_SET_INFORMATION ) = 0x0010

} // namespace horizon::win32