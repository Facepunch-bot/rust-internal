#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct ACTIVATION_CONTEXT;

struct RTL_ACTIVATION_CONTEXT_STACK_FRAME
{
	RTL_ACTIVATION_CONTEXT_STACK_FRAME* Previous = nullptr;	// 0x0000
	ACTIVATION_CONTEXT* ActivationContext = nullptr;				// 0x0008
	std::uint32_t Flags = 0;																// 0x0010
	FIELD_PAD( 0x0004 );																		// 0x0014
};
// sizeof( RTL_ACTIVATION_CONTEXT_STACK_FRAME ) = 0x0018

} // namespace horizon::win32