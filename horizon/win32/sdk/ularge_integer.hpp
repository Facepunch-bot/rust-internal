#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

union ULARGE_INTEGER
{
	union
	{
		struct
		{
			std::uint32_t LowPart;
			std::uint32_t HighPart;
		};
		struct
		{
			std::uint32_t LowPart;
			std::uint32_t HighPart;
		} u;
		std::uint64_t QuadPart = 0;
	};
};

} // namespace horizon::win32