#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "memory_working_set_ex_block.hpp"

namespace horizon::win32
{

struct MEMORY_WORKING_SET_EX_INFORMATION
{
	void* VirtualAddress = nullptr;													// 0x0000
	union
	{
		MEMORY_WORKING_SET_EX_BLOCK VirtualAttributes = { };	// 0x0008
		std::uintptr_t Long;																	// 0x0008
	} u1;																										// 0x0008
};
// sizeof( MEMORY_WORKING_SET_EX_INFORMATION ) = 0x0010

} // namespace horizon::win32