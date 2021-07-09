#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct RTL_BALANCED_NODE
{
	union
	{
		RTL_BALANCED_NODE* Children[ 2 ] = { };
		struct
		{
			RTL_BALANCED_NODE* Left;
			RTL_BALANCED_NODE* Right;
		};
	};
	union
	{
		std::uint8_t Red : 1;
		std::uint8_t Balance : 2;
		std::uint64_t ParentValue = 0;
	};
};

} // namespace horizon::win32