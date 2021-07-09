#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "list_entry.hpp"

namespace horizon::win32
{

struct PEB_LDR_DATA
{
	std::uint32_t Length = 0;													// 0x0000
	std::uint8_t Initialized = 0;											// 0x0004
	FIELD_PAD( 0x0003 );															// 0x0005
	void* SsHandle = nullptr;													// 0x0008
	LIST_ENTRY InLoadOrderModuleList = { };						// 0x0010
	LIST_ENTRY InMemoryOrderModuleList = { };					// 0x0020
	LIST_ENTRY InInitializationOrderModuleList = { };	// 0x0030
	void* EntryInProgress = nullptr;									// 0x0040
	std::uint8_t ShutdownInProgress = 0;							// 0x0048
	FIELD_PAD( 0x0007 );															// 0x0049
	void* ShutdownThreadId = nullptr;									// 0x0050
};
// sizeof( PEB_LDR_DATA ) = 0x0058 ( 88 )


} // namespace horizon::win32