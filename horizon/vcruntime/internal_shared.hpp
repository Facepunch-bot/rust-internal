#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

extern "C" {

	namespace atom::vcruntime
	{

	#pragma section( ".CRT$XCA", long, read )				// First C++ Initializer
	#pragma section( ".CRT$XCZ", long, read )				// Last C++ Initializer
	#pragma section( ".CRT$XDA", long, read )				// First Dynamic TLS Initializer
	#pragma section( ".CRT$XDZ", long, read )				// Last Dynamic TLS Initializer
	#pragma section( ".CRT$XIA", long, read )				// First C Initializer
	#pragma section( ".CRT$XIZ", long, read )				// Last C Initializer
	#pragma section( ".CRT$XLA", long, read )				// First Loader TLS Callback
	#pragma section( ".CRT$XLZ", long, read )				// Last Loader TLS Callback
	#pragma section( ".CRT$XPA", long, read )				// First Pre-Terminator
	#pragma section( ".CRT$XPZ", long, read )				// Last Pre-Terminator
	#pragma section( ".CRT$XTA", long, read )				// First Terminator
	#pragma section( ".CRT$XTZ", long, read )				// Last Terminator
	#pragma section( ".rdata$T", long, read )
	#pragma section( ".rtc$IAA", long, read )				// First RTC Initializer
	#pragma section( ".rtc$IZZ", long, read )				// Last RTC Initializer
	#pragma section( ".rtc$TAA", long, read )				// First RTC Terminator
	#pragma section( ".rtc$TZZ", long, read )				// Last RTC Terminator

	#define ATOM_COMMIT( name )											__declspec( allocate( name ) )

	using PVFV = void( * )( );
	using PIFV = int( * )( );

	extern ATOM_COMMIT( ".CRT$XIA" ) PIFV __xi_a[];	// First C Initializer
	extern ATOM_COMMIT( ".CRT$XIZ" ) PIFV __xi_z[];	// Last C Initializer
	extern ATOM_COMMIT( ".CRT$XCA" ) PVFV __xc_a[];	// First C++ Initializer
	extern ATOM_COMMIT( ".CRT$XCZ" ) PVFV __xc_z[];	// Last C++ Initializer
	extern ATOM_COMMIT( ".CRT$XPA" ) PVFV __xp_a[];	// First Pre-Terminator
	extern ATOM_COMMIT( ".CRT$XPZ" ) PVFV __xp_z[];	// Last Pre-Terminator
	extern ATOM_COMMIT( ".CRT$XTA" ) PVFV __xt_a[];	// First Terminator
	extern ATOM_COMMIT( ".CRT$XTZ" ) PVFV __xt_z[];	// Last Terminator


	} // namespace atom::vcruntime

}; // extern "C"