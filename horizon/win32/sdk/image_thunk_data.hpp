#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

constexpr std::uint32_t ImageOrdinalFlag32 = 0x80000000;
constexpr std::uint64_t ImageOrdinalFlag64 = 0x8000000000000000;

#if defined( HORIZON_X32 )
constexpr auto ImageOrdinalFlag = ImageOrdinalFlag32;
#elif defined( HORIZON_X64 )
constexpr auto ImageOrdinalFlag = ImageOrdinalFlag64;
#endif // HORIZON_X32

struct IMAGE_THUNK_DATA32
{
	union
	{
		std::uint32_t ForwarderString = 0;	// 0x0000
		std::uint32_t Function;							// 0x0000
		std::uint32_t Ordinal;							// 0x0000
		std::uint32_t AddressOfData;				// 0x0000
	} u1 = { };														// 0x0000
};
// sizeof( IMAGE_THUNK_DATA32 ) = 0x0004

struct IMAGE_THUNK_DATA64
{
	union
	{
		std::uint64_t ForwarderString = 0;	// 0x0000
		std::uint64_t Function;							// 0x0000
		std::uint64_t Ordinal;							// 0x0000
		std::uint64_t AddressOfData;				// 0x0000
	} u1 = { };														// 0x0000
};
// sizeof( IMAGE_THUNK_DATA64 ) = 0x0008

#if defined( HORIZON_X32 )
using IMAGE_THUNK_DATA = IMAGE_THUNK_DATA32;
#elif defined( HORIZON_X64 )
using IMAGE_THUNK_DATA = IMAGE_THUNK_DATA64;
#endif // HORIZON_X32

} // namespace horizon::win32