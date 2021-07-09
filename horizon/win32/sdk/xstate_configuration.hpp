#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "xstate_feature.hpp"

namespace horizon::win32
{

struct XSTATE_CONFIGURATION
{
	std::uint64_t EnabledFeatures = 0;
	std::uint64_t EnabledVolatileFeatures = 0;
	std::uint32_t Size = 0;
	union
	{
		std::uint32_t ControlFlags = 0;
		struct
		{
			std::uint32_t OptimizedSave : 1;
			std::uint32_t CompactionEnabled : 1;
		};
	};
	XSTATE_FEATURE Features[ 64 ] = { };
	std::uint64_t EnabledSupervisorFeatures = 0;
	std::uint64_t AlignedFeatures = 0;
	std::uint32_t AllFeatureSize = 0;
	std::uint32_t AllFeature[ 64 ] = { };
	FIELD_PAD( 0x0004 );
	std::uint64_t EnabledUserVisibleSupervisorFeatures = 0;
};
// sizeof( XSTATE_CONFIGURATION ) = 0x0338

} // namespace horizon::win32