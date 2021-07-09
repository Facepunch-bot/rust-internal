#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "nt_tib.hpp"
#include "client_id.hpp"
#include "peb.hpp"
#include "activation_context_stack.hpp"
#include "gdi_teb_batch.hpp"
#include "unicode_string.hpp"
#include "list_entry.hpp"
#include "guid.hpp"

namespace horizon::win32
{

struct TEB
{
	NT_TIB NtTib = { };																// 0x0000
	void* EnvironmentPointer = nullptr;								// 0x0038
	CLIENT_ID ClientId = { };													// 0x0040
	void* ActiveRpcHandle = nullptr;									// 0x0050
	void* ThreadLocalStoragePointer = nullptr;				// 0x0058
	PEB* ProcessEnvironmentBlock = nullptr;						// 0x0060
	std::uint32_t LastErrorValue = 0;									// 0x0068
	std::uint32_t CountOfOwnedCriticalSections = 0;		// 0x006C
	void* CsrClientThread = nullptr;									// 0x0070
	void* Win32ThreadInfo = nullptr;									// 0x0078
	std::uint32_t User32Reserved[ 26 ] = { };					// 0x0080
	std::uint32_t UserReserved[ 5 ] = { };						// 0x00
	FIELD_PAD( 0x0004 );															// 0x00
	void* WOW32Reserved = nullptr;										// 0x00
	std::uint32_t CurrentLocale = 0;									// 0x00
	std::uint32_t FpSoftwareStatusRegister = 0;				// 0x00
	void* ReservedForDebuggerInstrumentation[ 16 ] = { };
	void* SystemReserved1[ 30 ] = { };
	std::int8_t PlaceholderCompatibilityMode = 0;
	std::uint8_t PlaceholderHydrationAlwaysExplicit = 0;
	std::int8_t PlaceholderReserved[ 10 ] = { };
	std::uint32_t ProxiedProcessId = 0;
	ACTIVATION_CONTEXT_STACK _ActivationStack = { };
	std::uint8_t WorkingOnBehalfTicket[ 8 ] = { };
	std::int32_t ExceptionCode = 0;
	std::uint8_t Padding0[ 4 ] = { };
	ACTIVATION_CONTEXT_STACK* ActivationContextStackPointer = nullptr;
	std::uint64_t InstrumentationCallbackSp = 0;
	std::uint64_t InstrumentationCallbackPreviousPc = 0;
	std::uint64_t InstrumentationCallbackPreviousSp = 0;
	std::uint32_t TxFsContext = 0;
	std::uint8_t InstrumentationCallbackDisabled = 0;
	std::uint8_t UnalignedLoadStoreExceptions = 0;
	std::uint8_t Padding1[ 2 ] = { };
	GDI_TEB_BATCH GdiTebBatch = { };
	CLIENT_ID RealClientId = { };
	void* GdiCachedProcessHandle = nullptr;
	std::uint32_t GdiClientPID = 0;
	std::uint32_t GdiClientTID = 0;
	void* GdiThreadLocalInfo = nullptr;
	std::uint64_t Win32ClientInfo[ 62 ] = { };
	void* glDispatchTable[ 233 ] = { };
	std::uint64_t glReserved1[ 29 ] = { };
	void* glReserved2 = nullptr;
	void* glSectionInfo = nullptr;
	void* glSection = nullptr;
	void* glTable = nullptr;
	void* glCurrentRC = nullptr;
	void* glContext = nullptr;
	std::uint32_t LastStatusValue = 0;
	std::uint8_t Padding2[ 4 ] = { };
	UNICODE_STRING StaticUnicodeString = { };
	wchar_t StaticUnicodeBuffer[ 261 ] = { };
	std::uint8_t Padding3[ 6 ] = { };
	void* DeallocationStack = nullptr;
	void* TlsSlots[ 64 ] = { };
	LIST_ENTRY TlsLinks = { };
	void* Vdm = nullptr;
	void* ReservedForNtRpc = nullptr;
	void* DbgSsReserved[ 2 ] = { };
	std::uint32_t HardErrorMode = 0;
	std::uint8_t Padding4[ 4 ] = { };
	void* Instrumentation[ 11 ] = { };
	GUID ActivityId = { };
	void* SubProcessTag = nullptr;
	void* PerflibData = nullptr;
	void* EtwTraceData = nullptr;
	void* WinSockData = nullptr;
	std::uint32_t GdiBatchCount = 0;
	union
	{
		PROCESSOR_NUMBER CurrentIdealProcessor = { };
		std::uint32_t IdealProcessorValue;
		struct
		{
			std::uint8_t ReservedPad0;
			std::uint8_t ReservedPad1;
			std::uint8_t ReservedPad2;
			std::uint8_t IdealProcessor;
		};
	};
	std::uint32_t GuaranteedStackBytes = 0;
	std::uint8_t Padding5[ 4 ] = { };
	void* ReservedForPerf = nullptr;
	void* ReservedForOle = nullptr;
	std::uint32_t WaitingOnLoaderLock = 0;
	std::uint8_t Padding6[ 4 ] = { };
	void* SavedPriorityState = nullptr;
	std::uint64_t ReservedForCodeCoverage = 0;
	void* ThreadPoolData = nullptr;
	void** TlsExpansionSlots = nullptr;
	void* DeallocationBStore = nullptr;
	void* BStoreLimit = nullptr;
	std::uint32_t MuiGeneration = 0;
	std::uint32_t IsImpersonating = 0;
	void* NlsCache = nullptr;
	void* pShimData = nullptr;
	std::uint32_t HeapData = 0;
	std::uint8_t Padding7[ 4 ] = { };
	void* CurrentTransactionHandle = nullptr;
	void* ActiveFrame = nullptr;
	void* FlsData = nullptr;
	void* PreferredLanguages = nullptr;
	void* UserPrefLanguages = nullptr;
	void* MergedPrefLanguages = nullptr;
	std::uint32_t MuiImpersonation = 0;
	union
	{
		volatile std::uint16_t CrossTebFlags = 0;
		std::uint16_t SpareCrossTebBits : 16;
	};
	union
	{
		std::uint16_t SameTebFlags = 0;
		struct
		{
			std::uint16_t SafeThunkCall : 1;
			std::uint16_t InDebugPrint : 1;
			std::uint16_t HasFiberData : 1;
			std::uint16_t SkipThreadAttach : 1;
			std::uint16_t WerInShipAssertCode : 1;
			std::uint16_t RanProcessInit : 1;
			std::uint16_t ClonedThread : 1;
			std::uint16_t SupressDebugMsg : 1;
			std::uint16_t DisableUserStackWalk : 1;
			std::uint16_t RtlExceptionAttached : 1;
			std::uint16_t InitialThread : 1;
			std::uint16_t SessionAware : 1;
			std::uint16_t LoadOwner : 1;
			std::uint16_t LoaderWorker : 1;
			std::uint16_t SkipLoaderInit : 1;
			std::uint16_t SpareSameTebBits : 1;
		};
	};
	void* TxnScopeEnterCallback = nullptr;
	void* TxnScopeExitCallback = nullptr;
	void* TxnScopeContext = nullptr;
	std::uint32_t LockCount = 0;
	std::int32_t WowTebOffset = 0;
	void* ResourceRetValue = nullptr;
	void* ReservedForWdf = nullptr;
	std::uint64_t ReservedForCrt = 0;
	GUID EffectiveContainerId = { };
};

} // namespace horizon::win32