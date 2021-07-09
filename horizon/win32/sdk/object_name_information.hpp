#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "unicode_string.hpp"

namespace horizon::win32
{

struct OBJECT_NAME_INFORMATION
{
	UNICODE_STRING Name = { };	// 0x0000
};
// sizeof( OBJECT_NAME_INFORMATION ) = 0x0010

} // namespace horizon::win32