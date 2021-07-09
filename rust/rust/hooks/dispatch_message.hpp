#pragma once

#include "../../unity/sdk.hpp"

namespace rust::hooks
{

std::intptr_t API_STDCALL DispatchMessageA( const MSG* msg );

} // namespace rust::hooks