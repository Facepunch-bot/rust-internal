#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct MEMORY_SHARED_COMMIT_INFORMATION
{
	std::size_t CommitSize = 0;	// 0x0000
};
// sizeof( MEMORY_SHARED_COMMIT_INFORMATION ) = 0x0008

} // namespace horizon::win32