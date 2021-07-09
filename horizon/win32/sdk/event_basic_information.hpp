#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "event_type.hpp"

namespace horizon::win32
{

struct EVENT_BASIC_INFORMATION
{
	EVENT_TYPE EventType = NotificationEvent;	// 0x0000
	std::int32_t EventState = 0;							// 0x0004
};
// sizeof( EVENT_BASIC_INFORMATION ) = 0x0008

} // namespace horizon::win32