#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

enum SECTION_INHERIT
{
	ViewShare = 1,
	ViewUnmap,
};
// sizeof( SECTION_INHERIT ) = 0x0004

} // namespace horizon::win32