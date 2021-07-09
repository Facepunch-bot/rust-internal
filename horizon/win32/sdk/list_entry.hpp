#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct LIST_ENTRY32
{
	std::uint32_t Flink = 0;
	std::uint32_t Blink = 0;
};

struct LIST_ENTRY64
{
	std::uint64_t Flink = 0;
	std::uint64_t Blink = 0;
};

struct LIST_ENTRY
{
	LIST_ENTRY* Flink = nullptr;	// 0x0000
	LIST_ENTRY* Blink = nullptr;	// 0x0008
};
// sizeof( LIST_ENTRY ) = 0x0008

FORCEINLINE void InitializeListHead( LIST_ENTRY* ListHead )
{
	ListHead->Flink = ListHead->Blink = ListHead;
}

FORCEINLINE bool IsListEmpty( LIST_ENTRY* ListHead )
{
	return ( ListHead->Flink == ListHead );
}

FORCEINLINE bool RemoveEntryList( LIST_ENTRY* Entry )
{
	auto Flink = Entry->Flink;
	auto Blink = Entry->Blink;
	
	Blink->Flink = Flink;
	Flink->Blink = Blink;

	return ( Flink == Blink );
}

FORCEINLINE LIST_ENTRY* RemoveHeadList( LIST_ENTRY* ListHead )
{
	auto Entry = ListHead->Flink;
	auto Flink = Entry->Flink;
	
	ListHead->Flink = Flink;
	Flink->Blink = ListHead;

	return Entry;
}

FORCEINLINE LIST_ENTRY* RemoveTailList( LIST_ENTRY* ListHead )
{
	auto Entry = ListHead->Blink;
	auto Blink = Entry->Blink;

	ListHead->Blink = Blink;
	Blink->Flink = ListHead;

	return Entry;
}

FORCEINLINE void InsertTailList( LIST_ENTRY* ListHead, LIST_ENTRY* Entry )
{
	auto Blink = ListHead->Blink;

	Entry->Flink = ListHead;
	Entry->Blink = Blink;

	Blink->Flink = Entry;
	ListHead->Blink = Entry;
}

FORCEINLINE void InsertHeadList( LIST_ENTRY* ListHead, LIST_ENTRY* Entry )
{
	auto Flink = ListHead->Flink;

	Entry->Flink = Flink;
	Entry->Blink = ListHead;

	Flink->Blink = Entry;
	ListHead->Flink = Entry;
}

FORCEINLINE void AppendTailList( LIST_ENTRY* ListHead, LIST_ENTRY* ListToAppend )
{
	auto Blink = ListHead->Blink;

	ListHead->Blink->Flink = ListToAppend;
	ListHead->Blink = ListToAppend->Blink;

	ListToAppend->Blink->Flink = ListHead;
	ListToAppend->Blink = Blink;
}

} // namespace horizon::win32