#pragma once

#include <horizon/include/auto.hpp>
#include <horizon/include/base.hpp>
#include <horizon/include/win32.hpp>

#include <horizon/memory/operation.hpp>

#include "il2cpp-config-api.hpp"

#define ALIGN_OF( T )						__alignof( T )
#define ALIGN_TYPE( val )				
#define ALIGN_FIELD( val )			__declspec( align( val ) )

#define IL2CPP_PAGE_SIZE				4096

#define IL2CPP_ZERO_LEN_ARRAY		0

using Il2CppMethodSlot = std::uint32_t;
// sizeof( Il2CppMethodSlot ) = 0x0004

constexpr Il2CppMethodSlot kInvalidIl2CppMethodSlot = 65535;
// sizeof( kInvalidIl2CppMethodSlot ) = 0x0004

#define IL2CPP_DIR_SEPARATOR		'\\'

constexpr Il2CppChar kIl2CppNewLine[] = { '\r', '\n', '\0' };
// sizeof( kIl2CppNewLine ) = 0x0006