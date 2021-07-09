#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

constexpr std::uint32_t MemCommit = 0x00001000;
constexpr std::uint32_t MemReserve = 0x00002000;
constexpr std::uint32_t MemDecommit = 0x00004000;
constexpr std::uint32_t MemRelease = 0x00008000;
constexpr std::uint32_t MemFree = 0x00010000;
constexpr std::uint32_t MemPrivate = 0x00020000;
constexpr std::uint32_t MemMapped = 0x00040000;
constexpr std::uint32_t MemReset = 0x00080000;
constexpr std::uint32_t MemTopDown = 0x00100000;
constexpr std::uint32_t MemWriteWatch = 0x00200000;
constexpr std::uint32_t MemPhysical = 0x00400000;
constexpr std::uint32_t MemRotate = 0x00800000;
constexpr std::uint32_t MemDifferentImageBaseOk = 0x00800000;
constexpr std::uint32_t MemResetUndo = 0x01000000;
constexpr std::uint32_t MemLargePages = 0x02000000;
constexpr std::uint32_t Mem4MbPages = 0x08000000;

constexpr std::uint32_t MemImage = 0x01000000;

} // namespace horizon::win32