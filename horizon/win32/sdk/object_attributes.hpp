#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "unicode_string.hpp"

namespace horizon::win32
{

struct OBJECT_ATTRIBUTES
{
	std::uint32_t Length = 0;									// 0x0000
	FIELD_PAD( 0x0004 );											// 0x0004
	void* RootDirectory = nullptr;						// 0x0008
	UNICODE_STRING* ObjectName = nullptr;			// 0x0010
	std::uint32_t Attributes = 0;							// 0x0018
	FIELD_PAD( 0x0004 );											// 0x001C
	void* SecurityDescriptor = nullptr;				// 0x0020
	void* SecurityQualityOfService = nullptr;	// 0x0028
};
// sizeof( OBJECT_ATTRIBUTES ) = 0x0030

} // namespace horizon::win32