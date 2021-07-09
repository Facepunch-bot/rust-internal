#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

using ACCESS_MASK = std::uint32_t;
// sizeof( ACCESS_MASK ) = 0x0004

constexpr ACCESS_MASK AccessDelete = 0x00010000;
constexpr ACCESS_MASK AccessReadControl = 0x00020000;
constexpr ACCESS_MASK AccessWriteDAC = 0x00040000;
constexpr ACCESS_MASK AccessWriteOwner = 0x00080000;
constexpr ACCESS_MASK AccessSynchronize = 0x00100000;

constexpr ACCESS_MASK AccessStandardRightsRequired = 0x000F0000;

constexpr ACCESS_MASK AccessStandardRightsRead = AccessReadControl;
constexpr ACCESS_MASK AccessStandardRightsWrite = AccessReadControl;
constexpr ACCESS_MASK AccessStandardRightsExecute = AccessReadControl;

constexpr ACCESS_MASK AccessStandardRightsAll = 0x001F0000;
constexpr ACCESS_MASK AccessSpecificRightsAll = 0x0000FFFF;

constexpr ACCESS_MASK AccessSystemSecurity = 0x01000000;
constexpr ACCESS_MASK AccessMaximumAllowed = 0x02000000;

constexpr ACCESS_MASK AccessGenericRead = 0x80000000;
constexpr ACCESS_MASK AccessGenericWrite = 0x40000000;
constexpr ACCESS_MASK AccessGenericExecute = 0x20000000;
constexpr ACCESS_MASK AccessGenericAll = 0x10000000;

} // namespace horizon::win32