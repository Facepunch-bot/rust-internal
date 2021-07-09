#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

constexpr std::uint32_t SecBased = 0x00200000;
constexpr std::uint32_t SecNoChange = 0x00400000;
constexpr std::uint32_t SecFile = 0x00800000;
constexpr std::uint32_t SecImage = 0x01000000;
constexpr std::uint32_t SecProtectedImage = 0x02000000;
constexpr std::uint32_t SecReserve = 0x04000000;
constexpr std::uint32_t SecCommit = 0x08000000;
constexpr std::uint32_t SecNoCache = 0x10000000;
constexpr std::uint32_t SecGlobal = 0x20000000;
constexpr std::uint32_t SecWriteCombine = 0x40000000;
constexpr std::uint32_t SecLargePages = 0x80000000;
constexpr std::uint32_t SecImageNoExecute = ( SecImage | SecNoCache );

} // namespace horizon::win32