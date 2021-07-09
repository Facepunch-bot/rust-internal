#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct IMAGE_IMPORT_BY_NAME
{
	std::uint16_t Hint = 0;	// 0x0000
	char Name[ 1 ] = { };		// 0x0002
};
// sizeof( IMAGE_IMPORT_BY_NAME ) = 0x0004

} // namespace horizon::win32