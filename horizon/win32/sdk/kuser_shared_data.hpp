#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "ksystem_time.hpp"
#include "nt_product_type.hpp"
#include "alternative_architecture_type.hpp"
#include "large_integer.hpp"

namespace horizon::win32
{

struct KUSER_SHARED_DATA
{
	std::uint32_t TickCountLowDeprecated = 0;
	std::uint32_t TickCountMultiplier = 0;
	KSYSTEM_TIME InterruptTime = { };
	KSYSTEM_TIME SystemTime = { };
	KSYSTEM_TIME TimeZoneBias = { };
	std::uint16_t ImageNumberLow = 0;
	std::uint16_t ImageNumberHigh = 0;
	wchar_t NtSystemRoot[ 260 ] = { };
	std::uint32_t MaxStackTraceDepth = 0;
	std::uint32_t CryptoExponent = 0;
	std::uint32_t TimeZoneId = 0;
	std::uint32_t LargePageMinimum = 0;
	std::uint32_t AitSamplingValue = 0;
	std::uint32_t AppCompatFlag = 0;
	std::uint64_t RNGSeedVersion = 0;
	std::uint32_t GlobalValidationRunlevel = 0;
	std::int32_t TimeZoneBiasStamp = 0;
	std::uint32_t NtBuildNumber = 0;
	NT_PRODUCT_TYPE NtProductType = NtProductWinNt;
	std::uint8_t ProductTypeIsValid = 0;
	FIELD_PAD( 0x0001 );
	std::uint16_t NativeProcessorArchitecture = 0;
	std::uint32_t NtMajorVersion = 0;
	std::uint32_t NtMinorVersion = 0;
	std::uint8_t ProcessorFeatures[ 64 ] = { };
	FIELD_PAD( 0x0008 );
	std::uint32_t TimeSlip = 0;
	ALTERNATIVE_ARCHITECTURE_TYPE AlternativeArchitecture = StandardDesign;
	std::uint32_t BootId = 0;
	LARGE_INTEGER SystemExpirationDate = { };
	std::uint32_t SuiteMask = 0;
	std::uint8_t KdDebuggerEnabled = 0;
	union
	{
		std::uint8_t MitigationPolicies = 0;
		struct
		{
			std::uint8_t NXSupportPolicy : 2;
			std::uint8_t SEHValidationPolicy : 2;
			std::uint8_t CurDirDevicesSkippedForDlls : 2;
			std::uint8_t Reserved : 2;
		};
	};
	FIELD_PAD( 0x0002 );
	std::uint32_t ActiveConsoleId = 0;
	std::uint32_t DismountCount = 0;
	std::uint32_t ComPlusPackage = 0;
	std::uint32_t LastSystemRITEventTickCount = 0;
	std::uint32_t NumberOfPhysicalPages = 0;
	std::uint8_t SafeBootMode = 0;
	std::uint8_t VirtualizationFlags = 0;
	FIELD_PAD( 0x0002 );
	union
	{
		std::uint32_t SharedDataFlags = 0;
		struct
		{
			std::uint32_t DbgErrorPortPresent : 1;
			std::uint32_t DbgElevationEnabled : 1;
			std::uint32_t DbgVirtEnabled : 1;
			std::uint32_t DbgInstallerDetectEnabled : 1;
			std::uint32_t DbgLkgEnabled : 1;
			std::uint32_t DbgDynProcessorEnabled : 1;
			std::uint32_t DbgConsoleBrokerEnabled : 1;
			std::uint32_t DbgSecureBootEnabled : 1;
			std::uint32_t DbgMultiSessionSku : 1;
			std::uint32_t DbgMultiUsersInSessionSku : 1;
			std::uint32_t DbgStateSeparationEnabled : 1;
			std::uint32_t SpareBits : 21;
		};
	};
	FIELD_PAD( 0x0004 );
	std::uint64_t TestRetInstruction = 0;
	std::int64_t QpcFrequency = 0;
	std::uint32_t SystemCall = 0;
	FIELD_PAD( 0x0014 );
	union
	{
		KSYSTEM_TIME TickCount = { };
		std::uint64_t TickCountQuad;
		std::uint32_t ReservedTickCountOverlay[ 3 ];
	};
	FIELD_PAD( 0x0004 );
	std::uint32_t Cookie = 0;
	FIELD_PAD( 0x0004 );
	std::int64_t ConsoleSessionForegroundProcessId = 0;
	std::uint64_t TimeUpdateLock = 0;
	std::uint64_t BaselineSystemTimeQpc = 0;
	std::uint64_t BaselineInterruptTimeQpc = 0;
	std::uint64_t QpcSystemTimeIncrement = 0;
	std::uint64_t QpcInterruptTimeIncrement = 0;
	std::uint8_t QpcSystemTimeIncrementShift = 0;
	std::uint8_t QpcInterruptTimeIncrementShift = 0;
	std::uint16_t UnparkedProcessorCount = 0;
	std::uint32_t EnclaveFeatureMask[ 4 ] = { };
	std::uint32_t TelemetryCoverageRound = 0;
	std::uint16_t UserModeGlobalLogger[ 16 ] = { };
	std::uint32_t ImageFileExecutionOptions = 0;
	std::uint32_t LangGenerationCount = 0;
	FIELD_PAD( 0x0008 );
	std::uint64_t InterruptTimeBias = 0;
	std::uint64_t QpcBias = 0;
	std::uint32_t ActiveProcessorCount = 0;
	std::uint8_t ActiveGroupCount = 0;
	FIELD_PAD( 0x0001 );
	union
	{
		std::uint16_t QpcData = 0;
		struct
		{
			std::uint8_t QpcBypassEnabled;
			std::uint8_t QpcShift;
		};
	};
	LARGE_INTEGER TimeZoneBiasEffectiveStart = { };
	LARGE_INTEGER TimeZoneBiasEffectiveEnd = { };
};
// sizeof( KUSER_SHARED_DATA ) = 0x0710

} // namespace horizon::win32