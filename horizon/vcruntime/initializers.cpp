#include "initializers.hpp"
#include "internal_shared.hpp"

#include "../memory/operation.hpp"
#include "../win32/trace.hpp"
#include "../win32/process.hpp"

#pragma comment( linker, "/merge:.CRT=.rdata" )

using namespace horizon;

// 
// Initializer and Terminator Support
// 
using PVFV = void( * )();
using PIFV = int( * )();
using PVFI = void( * )( int );

namespace atom::vcruntime
{

extern "C" ATOM_COMMIT( ".CRT$XIA" ) PIFV __xi_a[] = { nullptr };	// C initializers (first)
extern "C" ATOM_COMMIT( ".CRT$XIZ" ) PIFV __xi_z[] = { nullptr };	// C initializers (last)

extern "C" ATOM_COMMIT( ".CRT$XCA" ) PVFV __xc_a[] = { nullptr };	// C++ initializers (first)
extern "C" ATOM_COMMIT( ".CRT$XCZ" ) PVFV __xc_z[] = { nullptr };	// C++ initializers (last)

extern "C" ATOM_COMMIT( ".CRT$XPA" ) PVFV __xp_a[] = { nullptr };	// C pre-terminators (first)
extern "C" ATOM_COMMIT( ".CRT$XPZ" ) PVFV __xp_z[] = { nullptr };	// C pre-terminators (last)

extern "C" ATOM_COMMIT( ".CRT$XTA" ) PVFV __xt_a[] = { nullptr };	// C terminators (first)
extern "C" ATOM_COMMIT( ".CRT$XTZ" ) PVFV __xt_z[] = { nullptr };	// C terminators (last)

} // namespace atom::vcruntime

constexpr auto MaximumTerminatorCount = 512;

PVFV g_on_exit_array[ MaximumTerminatorCount ] = { };

PVFV* g_on_exit_begin = nullptr;
PVFV* g_on_exit_end = nullptr;

namespace atom::vcruntime
{

Initializers::~Initializers()
{
	Destroy();
}

bool Initializers::Create()
{
	m_end = m_begin = m_array;
	*m_begin = nullptr;

	int code = ExecuteConstructorArray( __xi_a, __xi_z );

	if( code )
	{
		TRACE( "%s: ExecuteConstructorArray(...) error!", ATOM_FUNCTION );
		return false;
	}

	ExecuteConstructorArray( __xc_a, __xc_z );
	return true;
}

void Initializers::Destroy()
{
	if( m_end )
	{
		while( m_end-- >= m_begin )
		{
			if( *m_end )
			{
				( *m_end )();
			}
		}
	}

	ExecuteConstructorArray( __xp_a, __xp_z );
	ExecuteConstructorArray( __xt_a, __xt_z );
}

int Initializers::ExecuteConstructorArray( PIFV* begin, PIFV* end )
{
	auto constructor = begin;

	while( constructor != end )
	{
		if( *constructor )
		{
			int code = ( *constructor )();
			
			if( code )
			{
				return code;
			}
		}

		constructor++;
	}

	return 0;
}

void Initializers::ExecuteConstructorArray( PVFV* begin, PVFV* end )
{
	auto constructor = begin;

	while( constructor != end )
	{
		if( *constructor )
		{
			( *constructor )();
		}

		constructor++;
	}
}

void init_on_exit_array()
{
	g_on_exit_begin = g_on_exit_array;
	g_on_exit_end = g_on_exit_array;

	( *g_on_exit_begin ) = nullptr;
}

int execute_pifv_array( PIFV* begin, PIFV* end )
{
	auto procedure = begin;

	while( procedure != end )
	{
		if( *procedure )
		{
			int code = ( *procedure )();
			TRACE( "pifv @ 0x%016llX returned %d", memory::ToAddress( *procedure ), code );

			if( code )
			{
				return code;
			}
		}

		procedure++;
	}

	return 0;
}

void execute_pvfv_array( PVFV* begin, PVFV* end )
{
	auto procedure = begin;

	while( procedure != end )
	{
		if( *procedure )
		{
			( *procedure )();
			TRACE( "pvfv @ 0x%016llX", memory::ToAddress( *procedure ) );
		}

		procedure++;
	}
}

int ExecuteArray( PIFV* begin, PIFV* end )
{
	auto procedure = begin;

	while( procedure != end )
	{
		if( *procedure )
		{
			const auto code = ( **procedure )();
			TRACE( "%s: 'PIFV' @ '0x%016llX' returned '%d'", ATOM_FUNCTION, memory::ToAddress( *procedure ), code );

			if( code )
			{
				return code;
			}
		}

		procedure++;
	}

	return 0;
}

void ExecuteArray( PVFV* begin, PVFV* end )
{
	auto procedure = begin;

	while( procedure != end )
	{
		if( *procedure )
		{
			( **procedure )();
			TRACE( "%s: 'procedure' @ '0x%016llX'", ATOM_FUNCTION, memory::ToAddress( *procedure ) );
		}

		procedure++;
	}
}

int ExecuteInitializers()
{
	g_on_exit_begin = g_on_exit_array;
	g_on_exit_end = g_on_exit_array;

	( *g_on_exit_begin ) = nullptr;

	// 
	// try execute C constructors
	// 
	const auto code = ExecuteArray( __xi_a, __xi_z );

	if( code )
	{
		return code;
	}

	// 
	// execute C++ constructors
	// 
	ExecuteArray( __xc_a, __xc_z );
	return 0;
}

void ExecuteTerminators()
{
	if( memory::IsAddressValid( g_on_exit_begin ) )
	{
		// 
		// execute 'atexit' terminators
		// 
		for( auto procedure = g_on_exit_end; procedure >= g_on_exit_begin; procedure-- )
		{
			if( *procedure )
			{
				( **procedure )();
			}
		}
	}

	// 
	// execute C pre-terminators & terminators
	// 
	ExecuteArray( __xp_a, __xp_z );
	ExecuteArray( __xt_a, __xt_z );
}

} // namespace atom::vcruntime

int crt_init()
{
	atom::vcruntime::init_on_exit_array();
	int code = atom::vcruntime::execute_pifv_array( atom::vcruntime::__xi_a, atom::vcruntime::__xi_z );
	if( code )
	{
		return code;
	}
	atom::vcruntime::execute_pvfv_array( atom::vcruntime::__xc_a, atom::vcruntime::__xc_z );
	return 0;
}

void crt_uninit()
{
	if( g_on_exit_begin )
	{
		for( auto fn = g_on_exit_end; fn >= g_on_exit_begin; fn-- )
		{
			if( *fn )
			{
				( **fn )();
			}
		}
	}
	atom::vcruntime::execute_pvfv_array( atom::vcruntime::__xp_a, atom::vcruntime::__xp_z );
	atom::vcruntime::execute_pvfv_array( atom::vcruntime::__xt_a, atom::vcruntime::__xt_z );
}

extern "C"
{

	int atexit( PVFV procedure )
	{
		// 
		// is 'g_on_exit_array' overflow
		// 
		if( g_on_exit_end > &g_on_exit_array[ MaximumTerminatorCount - 1 ] )
		{
			TRACE( "%s: 'g_on_exit_array' overflow!", ATOM_FUNCTION );
			return 1;
		}

		// 
		// emplace procedure at the end of array
		// 
		( *g_on_exit_end ) = procedure;
		TRACE( "%s: 'procedure' @ '0x%016llX'", ATOM_FUNCTION, memory::ToAddress( procedure ) );

		// 
		// increment end pointer
		// 
		g_on_exit_end++;
		return 0;
	}

}; // extern "C"