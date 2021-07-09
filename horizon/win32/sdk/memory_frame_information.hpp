#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct MEMORY_FRAME_INFORMATION
{
	std::uint64_t UseDescription : 4;		// 0x0000
	std::uint64_t ListDescription : 3;	// 0x0000
	std::uint64_t Cold : 1;							// 0x0000
	std::uint64_t Pinned : 1;						// 0x0000
	std::uint64_t DontUse : 48;					// 0x0000
	std::uint64_t Priority : 3;					// 0x0000
	std::uint64_t Reserved : 4;					// 0x0000
};
// sizeof( MEMORY_FRAME_INFORMATION ) = 0x0008

} // namespace horizon::win32