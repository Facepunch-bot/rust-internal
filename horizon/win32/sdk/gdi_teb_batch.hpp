#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct GDI_TEB_BATCH
{
	struct
	{
		std::uint32_t Offset : 31;							// 0x0000
		std::uint32_t HasRenderingCommand : 1;	// 0x0000
	};
	FIELD_PAD( 0x0004 );											// 0x0004
	std::uint64_t HDC = 0;										// 0x0008
	std::uint32_t Buffer[ 310 ] = { };				// 0x0010
};
// sizeof( GDI_TEB_BATCH ) = 0x04E8

} // namespace horizon::win32