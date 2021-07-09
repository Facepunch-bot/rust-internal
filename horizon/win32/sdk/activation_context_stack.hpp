#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "rtl_activation_context_stack_frame.hpp"
#include "list_entry.hpp"

namespace horizon::win32
{

struct ACTIVATION_CONTEXT_STACK
{
	RTL_ACTIVATION_CONTEXT_STACK_FRAME* ActiveFrame = nullptr;	// 0x0000
	LIST_ENTRY FrameListCache = { };														// 0x0008
	std::uint32_t Flags = 0;																		// 0x0018
	std::uint32_t NextCookieSequenceNumber = 0;									// 0x001C
	std::uint32_t StackId = 0;																	// 0x0020
	FIELD_PAD( 0x0004 );																				// 0x0024
};
// sizeof( ACTIVATION_CONTEXT_STACK ) = 0x0028

} // namespace horizon::win32