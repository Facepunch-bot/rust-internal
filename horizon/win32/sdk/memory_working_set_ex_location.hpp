#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

enum MEMORY_WORKING_SET_EX_LOCATION
{
	MemoryLocationInvalid,
	MemoryLocationResident,
	MemoryLocationPagefile,
	MemoryLocationReserved,
};
// sizeof( MEMORY_WORKING_SET_EX_LOCATION ) = 0x0004

} // namespace horizon::win32