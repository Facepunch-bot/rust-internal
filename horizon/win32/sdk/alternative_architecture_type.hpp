#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

enum ALTERNATIVE_ARCHITECTURE_TYPE
{
	StandardDesign = 0,
	NEC98x86 = 1,
	EndAlternatives = 2,
};
// sizeof( ALTERNATIVE_ARCHITECTURE_TYPE ) = 0x0004

} // namespace horizon::win32