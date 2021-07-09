#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "access_mask.hpp"
#include "large_integer.hpp"

namespace horizon::win32
{

struct OBJECT_BASIC_INFORMATION
{
	std::uint32_t Attributes = 0;								// 0x0000
	ACCESS_MASK DesiredAccess = 0;							// 0x0004
	std::uint32_t HandleCount = 0;							// 0x0008
	std::uint32_t ReferenceCount = 0;						// 0x000C
	std::uint32_t PagedPoolUsage = 0;						// 0x0010
	std::uint32_t NonPagedPoolUsage = 0;				// 0x0014
	std::uint32_t Reserved[ 3 ] = { };					// 0x0018
	std::uint32_t NameInformationLength = 0;		// 0x0024
	std::uint32_t TypeInformationLength = 0;		// 0x0028
	std::uint32_t SecurityDescriptorLength = 0;	// 0x002C
	LARGE_INTEGER CreationTime = { };						// 0x0020
};
// sizeof( OBJECT_BASIC_INFORMATION ) = 0x0028

} // namespace horizon::win32