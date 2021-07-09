#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

enum MEMORY_INFORMATION_CLASS
{
	MemoryBasicInformation,
	MemoryWorkingSetInformation,
	MemoryMappedFilenameInformation,
	MemoryRegionInformation,
	MemoryWorkingSetExInformation,
	MemorySharedCommitInformation,
	MemoryImageInformation,
	MemoryRegionInformationEx,
	MemoryPrivilegedBasicInformation,
	MemoryEnclaveImageInformation,
};
// sizeof( MEMORY_INFORMATION_CLASS ) = 0x0004

} // namespace horizon::win32