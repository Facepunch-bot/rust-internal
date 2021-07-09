#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct CLIENT_ID32
{
	std::uint32_t UniqueProcess = 0;
	std::uint32_t UniqueThread = 0;
};

struct CLIENT_ID64
{
	std::uint64_t UniqueProcess = 0;
	std::uint64_t UniqueThread = 0;
};

struct CLIENT_ID
{
	void* UniqueProcess = nullptr;
	void* UniqueThread = nullptr;
};

} // namespace horizon::win32