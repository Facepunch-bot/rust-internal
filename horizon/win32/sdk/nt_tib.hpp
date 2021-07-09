#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "exception_registration_record.hpp"

namespace horizon::win32
{

struct NT_TIB32
{
	std::uint32_t ExceptionList = 0;
	std::uint32_t StackBase = 0;
	std::uint32_t StackLimit = 0;
	std::uint32_t SubSystemTib = 0;
	union
	{
		std::uint32_t FiberData = 0;
		std::uint32_t Version;
	};
	std::uint32_t ArbitraryUserPointer = 0;
	std::uint32_t Self = 0;
};

struct NT_TIB64
{
	std::uint64_t ExceptionList = 0;
	std::uint64_t StackBase = 0;
	std::uint64_t StackLimit = 0;
	std::uint64_t SubSystemTib = 0;
	union
	{
		std::uint64_t FiberData = 0;
		std::uint32_t Version;
	};
	std::uint64_t ArbitraryUserPointer = 0;
	std::uint64_t Self = 0;
};

struct NT_TIB
{
	EXCEPTION_REGISTRATION_RECORD* ExceptionList = nullptr;
	void* StackBase = nullptr;
	void* StackLimit = nullptr;
	void* SubSystemTib = nullptr;
	union
	{
		void* FiberData = nullptr;
		std::uint32_t Version;
	};
	void* ArbitraryUserPointer = nullptr;
	NT_TIB* Self = nullptr;
};

} // namespace horizon::win32