#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

enum OBJECT_INFORMATION_CLASS
{
	ObjectBasicInformation,
	ObjectNameInformation,
	ObjectTypeInformation,
	ObjectAllInformation,
	ObjectDataInformation,
};
// sizeof( OBJECT_INFORMATION_CLASS ) = 0x0004

} // namespace horizon::win32