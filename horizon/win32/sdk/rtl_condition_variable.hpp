#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct RTL_CONDITION_VARIABLE
{
	void* Ptr = nullptr;	// 0x0000
};
// sizeof( RTL_CONDITION_VARIABLE ) = 0x0008

} // horizon::win32