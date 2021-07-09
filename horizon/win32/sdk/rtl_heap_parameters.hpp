#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct RTL_HEAP_PARAMETERS
{
	std::uint32_t Length = 0;										// 0x0000
	FIELD_PAD( 0x0004 );												// 0x0004
	std::size_t SegmentReserve = 0;							// 0x0008
	std::size_t SegmentCommit = 0;							// 0x0010
	std::size_t DeCommitFreeBlockThreshold = 0;	// 0x0018
	std::size_t DeCommitTotalFreeThreshold = 0;	// 0x0020
	std::size_t MaximumAllocationSize = 0;			// 0x0028
	std::size_t VirtualMemoryThreshold = 0;			// 0x0030
	std::size_t InitialCommit = 0;							// 0x0038
	std::size_t InitialReserve = 0;							// 0x0040
	void* CommitRoutine = nullptr;							// 0x0048
	std::size_t Reserved[ 2 ] = { };						// 0x0050
};
// sizeof( RTL_HEAP_PARAMETERS ) = 0x0060

} // namespace horizon::win32