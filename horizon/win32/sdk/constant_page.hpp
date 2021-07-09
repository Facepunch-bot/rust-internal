#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

constexpr std::uint32_t PageNoAccess = 0x00000001;
constexpr std::uint32_t PageReadOnly = 0x00000002;
constexpr std::uint32_t PageReadWrite = 0x00000004;
constexpr std::uint32_t PageWriteCopy = 0x00000008;
constexpr std::uint32_t PageExecute = 0x00000010;
constexpr std::uint32_t PageExecuteRead = 0x00000020;
constexpr std::uint32_t PageExecuteReadWrite = 0x00000040;
constexpr std::uint32_t PageExecuteWriteCopy = 0x00000080;
constexpr std::uint32_t PageGuard = 0x00000100;
constexpr std::uint32_t PageNoCache = 0x00000200;
constexpr std::uint32_t PageWriteCombine = 0x00000400;

} // namespace horizon::win32