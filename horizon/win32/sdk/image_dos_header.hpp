#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

constexpr std::uint16_t ImageDosSignature = 0x5A4D;	// 'MZ'

struct IMAGE_DOS_HEADER
{
	std::uint16_t e_magic = 0;				// 0x0000
	std::uint16_t e_cblp = 0;					// 0x0002
	std::uint16_t e_cp = 0;						// 0x0004
	std::uint16_t e_crlc = 0;					// 0x0006
	std::uint16_t e_cparhdr = 0;			// 0x0008
	std::uint16_t e_minalloc = 0;			// 0x000A
	std::uint16_t e_maxalloc = 0;			// 0x000C
	std::uint16_t e_ss = 0;						// 0x000E
	std::uint16_t e_sp = 0;						// 0x0010
	std::uint16_t e_csum = 0;					// 0x0012
	std::uint16_t e_ip = 0;						// 0x0014
	std::uint16_t e_cs = 0;						// 0x0016
	std::uint16_t e_lfarlc = 0;				// 0x0018
	std::uint16_t e_ovno = 0;					// 0x001A
	std::uint16_t e_res[ 4 ] = { };		// 0x001C
	std::uint16_t e_oemid = 0;				// 0x0024
	std::uint16_t e_oeminfo = 0;			// 0x0026
	std::uint16_t e_res2[ 10 ] = { };	// 0x0028
	std::uint32_t e_lfanew = 0;				// 0x003C
};
// sizeof( IMAGE_DOS_HEADER ) = 0x0040

} // namespace horizon::win32