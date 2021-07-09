#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "peb_ldr_data.hpp"
#include "large_integer.hpp"
#include "ularge_integer.hpp"

namespace horizon::win32
{

struct PEB
{
	std::uint8_t InheritedAddressSpace = 0;
	std::uint8_t ReadImageFileExecOptions = 0;
	std::uint8_t BeingDebugged = 0;
	union
	{
		std::uint8_t BitField = 0;
		struct
		{
			std::uint8_t ImageUsesLargePages : 1;
			std::uint8_t IsProtectedProcess : 1;
			std::uint8_t IsImageDynamicallyRelocated : 1;
			std::uint8_t SkipPatchingUser32Forwarders : 1;
			std::uint8_t IsPackagedProcess : 1;
			std::uint8_t IsAppContainer : 1;
			std::uint8_t IsProtectedProcessLight : 1;
			std::uint8_t IsLongPathAwareProcess : 1;
		};
	};
	FIELD_PAD( 0x0004 );
	void* Mutant = nullptr;
	void* ImageBaseAddress = nullptr;
	PEB_LDR_DATA* Ldr = nullptr;
	void* ProcessParameters = nullptr;
	void* SubSystemData = nullptr;
	void* ProcessHeap = nullptr;
	void* FastPebLock = nullptr;
	void* volatile AtlThunkSListPtr = nullptr;
	void* IFEOKey = nullptr;
	union
	{
		std::uint32_t CrossProcessFlags = 0;
		struct
		{
			std::uint32_t ProcessInJob : 1;
			std::uint32_t ProcessInitializing : 1;
			std::uint32_t ProcessUsingVEH: 1;
			std::uint32_t ProcessUsingVCH: 1;
			std::uint32_t ProcessUsingFTH: 1;
			std::uint32_t ProcessPreviouslyThrottled : 1;
			std::uint32_t ProcessCurrentlyThrottled : 1;
			std::uint32_t ProcessImagesHotPatched : 1;
			std::uint32_t ReservedBits0 : 1;
		};
	};
	FIELD_PAD( 0x0004 );
	union
	{
		void* KernelCallbackTable = nullptr;
		void* UserSharedInfoPtr;
	};
	FIELD_PAD( 0x0004 );
	std::uint32_t AtlThunkSListPtr32 = 0;
	void* ApiSetMap = nullptr;
	std::uint32_t TlsExpansionCounter = 0;
	FIELD_PAD( 0x0004 );
	void* TlsBitmap = nullptr;
	std::uint32_t TlsBitmapBits[ 2 ] = { };
	void* ReadOnlySharedMemoryBase = nullptr;
	void* SharedData = nullptr;
	void** ReadOnlyStaticServerData = nullptr;
	void* AnsiCodePageData = nullptr;
	void* OemCodePageData = nullptr;
	void* UnicodeCaseTableData = nullptr;
	std::uint32_t NumberOfProcessors = 0;
	std::uint32_t NtGlobalFlag = 0;
};

} // namespace horizon::win32