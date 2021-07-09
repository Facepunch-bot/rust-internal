#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct MUTANT_BASIC_INFORMATION
{
	std::int32_t CurrentCount = 0;		// 0x0000
	std::uint8_t OwnedByCaller = 0;		// 0x0004
	std::uint8_t AbandonedState = 0;	// 0x0005
	FIELD_PAD( 0x0002 );							// 0x0006
};
// sizeof( MUTANT_BASIC_INFORMATION ) = 0x0008

} // namespace horizon::win32