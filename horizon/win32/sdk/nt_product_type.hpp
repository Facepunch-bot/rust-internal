#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

enum NT_PRODUCT_TYPE
{
	NtProductWinNt = 1,
	NtProductLanManNt = 2,
	NtProductServer = 3,
};
// sizeof( NT_PRODUCT_TYPE ) = 0x0004

} // namespace horizon::win32