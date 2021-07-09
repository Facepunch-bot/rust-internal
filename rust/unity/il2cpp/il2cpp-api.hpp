#pragma once

#include <horizon/include/auto.hpp>
#include <horizon/include/base.hpp>
#include <horizon/include/win32.hpp>

#include <horizon/memory/operation.hpp>

#include "il2cpp-config-api.hpp"
#include "il2cpp-class-internals.hpp"
#include "il2cpp-object-internals.hpp"

#define DO_API( return_type, name, parameters )	extern return_type ( *name ) parameters

