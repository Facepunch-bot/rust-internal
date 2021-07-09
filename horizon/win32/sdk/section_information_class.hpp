#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

enum SECTION_INFORMATION_CLASS
{
	SectionBasicInformation,
	SectionImageInformation,
	SectionRelocationInformation,
};
// sizeof( SECTION_INFORMATION_CLASS ) = 0x0004

} // namespace horizon::win32