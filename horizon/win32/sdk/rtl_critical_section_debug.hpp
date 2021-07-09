#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "list_entry.hpp"

namespace horizon::win32
{

struct RTL_CRITICAL_SECTION;

struct RTL_CRITICAL_SECTION_DEBUG
{
	std::uint16_t Type = 0;														// 0x0000
	std::uint16_t CreatorBackTraceIndex = 0;					// 0x0002
	FIELD_PAD( 0x0004 );															// 0x0004
	RTL_CRITICAL_SECTION* CriticalSection = nullptr;	// 0x0008
	LIST_ENTRY ProcessLocksList = { };								// 0x0010
	std::uint32_t EntryCount = 0;											// 0x0020
	std::uint32_t ContentionCount = 0;								// 0x0024
	std::uint32_t Flags = 0;													// 0x0028
	std::uint16_t CreatorBackTraceIndexHigh = 0;			// 0x002C
	FIELD_PAD( 0x0002 );															// 0x002E
};
// sizeof( RTL_CRITICAL_SECTION_DEBUG ) = 0x0030 ( 48 )

} // namespace horizon::win32