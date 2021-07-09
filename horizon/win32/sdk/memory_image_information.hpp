#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct MEMORY_IMAGE_INFORMATION
{
	void* ImageBase = nullptr;								// 0x0000
	std::size_t SizeOfImage = 0;							// 0x0008
	union
	{
		std::uint32_t ImageFlags = 0;						// 0x0010
		struct
		{
			std::uint32_t ImagePartialMap : 1;		// 0x0010
			std::uint32_t ImageNotExecutable : 1;	// 0x0010
			std::uint32_t ImageSigningLevel : 4;	// 0x0010
			std::uint32_t Reserved : 26;					// 0x0010
		};
	};
	FIELD_PAD( 0x0004 );											// 0x0014
};
// sizeof( MEMORY_IMAGE_INFORMATION ) = 0x0018

} // namespace horizon::win32