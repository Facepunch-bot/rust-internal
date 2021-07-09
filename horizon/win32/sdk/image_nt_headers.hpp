#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

#include "image_file_header.hpp"
#include "image_optional_header.hpp"

namespace horizon::win32
{

constexpr std::uint32_t ImageNtSignature = 0x00004550;	// 'PE00'

struct IMAGE_NT_HEADERS32
{
	std::uint32_t Signature = 0;									// 0x0000
	IMAGE_FILE_HEADER FileHeader = { };						// 0x0004
	IMAGE_OPTIONAL_HEADER32 OptionalHeader = { };	// 0x0018
};
// sizeof( IMAGE_NT_HEADERS32 ) = 0x00F8

struct IMAGE_NT_HEADERS64
{
	std::uint32_t Signature = 0;									// 0x0000
	IMAGE_FILE_HEADER FileHeader = { };						// 0x0004
	IMAGE_OPTIONAL_HEADER64 OptionalHeader = { };	// 0x0018
};
// sizeof( IMAGE_NT_HEADERS32 ) = 0x0108

#if defined( HORIZON_X32 )
using IMAGE_NT_HEADERS = IMAGE_NT_HEADERS32;
#elif defined( HORIZON_X64 )
using IMAGE_NT_HEADERS = IMAGE_NT_HEADERS64;
#endif // HORIZON_X32

} // namespace horizon::win32