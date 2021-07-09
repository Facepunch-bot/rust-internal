#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct MEMORY_WORKING_SET_BLOCK
{
	std::uintptr_t Protection : 5;		// 0x0000
	std::uintptr_t ShareCount : 3;		// 0x0000
	std::uintptr_t Shared : 1;				// 0x0000
	std::uintptr_t Node : 3;					// 0x0000
#if defined( HORIZON_X32 )
	std::uintptr_t VirtualPage : 20;	// 0x0000
#elif defined( HORIZON_X64 )
	std::uintptr_t VirtualPage : 52;	// 0x0000
#endif // HORIZON_X32
};
// sizeof( MEMORY_WORKING_SET_BLOCK ) = 0x0008

} // namespace horizon::win32