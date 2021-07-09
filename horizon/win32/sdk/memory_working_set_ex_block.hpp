#pragma once

#include "../../include/auto.hpp"
#include "../../include/base.hpp"
#include "../../include/win32.hpp"

namespace horizon::win32
{

struct MEMORY_WORKING_SET_EX_BLOCK
{
	union
	{
		struct
		{
			std::uintptr_t Valid : 1;										// 0x0000
			std::uintptr_t ShareCount : 3;							// 0x0000
			std::uintptr_t Win32Protection : 11;				// 0x0000
			std::uintptr_t Shared : 1;									// 0x0000
			std::uintptr_t Node : 6;										// 0x0000
			std::uintptr_t Locked : 1;									// 0x0000
			std::uintptr_t LargePage : 1;								// 0x0000
			std::uintptr_t Priority : 3;								// 0x0000
			std::uintptr_t Reserved0 : 3;								// 0x0000
			std::uintptr_t SharedOriginal : 1;					// 0x0000
			std::uintptr_t Bad : 1;											// 0x0000
			std::uintptr_t Win32GraphicsProtection : 4;	// 0x0000
#if defined( HORIZON_X64 )
			std::uintptr_t Reserved1 : 28;							// 0x0000
#endif // HORIZON_X64
		};
		struct
		{
			std::uintptr_t Valid : 1;										// 0x0000
			std::uintptr_t Reserved0 : 14;							// 0x0000
			std::uintptr_t Shared : 1;									// 0x0000
			std::uintptr_t Reserved1 : 5;								// 0x0000
			std::uintptr_t PageTable : 1;								// 0x0000
			std::uintptr_t Location : 2;								// 0x0000
			std::uintptr_t Priority : 3;								// 0x0000
			std::uintptr_t ModifiedList : 1;						// 0x0000
			std::uintptr_t Reserved2 : 2;								// 0x0000
			std::uintptr_t SharedOriginal : 1;					// 0x0000
			std::uintptr_t Bad : 1;											// 0x0000
#if defined( HORIZON_X64 )
			std::uintptr_t Reserved3 : 32;							// 0x0000
#endif // HORIZON_X64
		} Invalid;																		// 0x0000
	};
};
// sizeof( MEMORY_WORKING_SET_EX_BLOCK ) = 0x0008

} // namespace horizon::win32