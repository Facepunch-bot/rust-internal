#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "io_status_block.hpp"

namespace horizon::win32
{

using IO_APC_ROUTINE =
void( * )( void* ApcContext,
					 IO_STATUS_BLOCK* IoStatusBlock,
					 std::uint32_t Reserved );

} // namespace horizon::win32