#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "rtl_critical_section_debug.hpp"

namespace horizon::win32
{

struct RTL_CRITICAL_SECTION
{
	RTL_CRITICAL_SECTION_DEBUG* DebugInfo = nullptr;	// 0x0000
	std::int32_t LockCount = 0;												// 0x0008
	std::int32_t RecursionCount = 0;									// 0x000C
	void* OwningThread = nullptr;											// 0x0010
	void* LockSemaphore = nullptr;										// 0x0018
	std::uint64_t SpinCount = 0;											// 0x0020
};
// sizeof( RTL_CRITICAL_SECTION ) = 0x0028 ( 40 )

} // namespace horizon::win32