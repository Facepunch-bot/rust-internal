#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct IO_STATUS_BLOCK
{
	union
	{
		std::int32_t Status;					// 0x0000
		void* Pointer = nullptr;			// 0x0000
	};
	std::uint32_t Information = 0;	// 0x0000
	FIELD_PAD( 0x0004 );						// 0x0004
};
// sizeof( IO_STATUS_BLOCK ) = 0x0008

} // namespace horizon::win32