#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

union LARGE_INTEGER
{
	union
	{
		struct
		{
			std::uint32_t LowPart;		// 0x0000
			std::int32_t HighPart;		// 0x0004
		};
		struct
		{
			std::uint32_t LowPart;		// 0x0000
			std::int32_t HighPart;		// 0x0004
		} u;
		std::int64_t QuadPart = 0;	// 0x0000
	};
};
// sizeof( LARGE_INTEGER ) = 0x0008

} // namespace horizon::win32