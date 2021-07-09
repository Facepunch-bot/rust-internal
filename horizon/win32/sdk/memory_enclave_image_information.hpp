#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "memory_image_information.hpp"

namespace horizon::win32
{

struct MEMORY_ENCLAVE_IMAGE_INFORMATION
{
	MEMORY_IMAGE_INFORMATION ImageInfo = { };	// 0x0000
	std::uint8_t UniqueID[ 32 ] = { };				// 0x0018
	std::uint8_t AuthorID[ 32 ] = { };				// 0x0038
};
// sizeof( MEMORY_ENCLAVE_IMAGE_INFORMATION ) = 0x0058

} // namespace horizon::win32