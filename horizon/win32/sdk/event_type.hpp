#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

enum EVENT_TYPE
{
	NotificationEvent,
	SynchronizationEvent,
};
// sizeof( EVENT_TYPE ) = 0x0004

} // namespace horizon::win32