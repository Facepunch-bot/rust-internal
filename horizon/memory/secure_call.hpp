#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "../constant/character.hpp"
#include "../constant/hash.hpp"
#include "../constant/secure_string.hpp"
#include "../constant/string.hpp"

#include "../win32/image.hpp"

#include "arg_stack.hpp"
#include "operation.hpp"
#include "scan.hpp"

// FF 23				| jmp qword ptr [rbx]
// FF 26				| jmp qword ptr [rsi]
// FF 27				| jmp qword ptr [rdi]
// FF 65 00			| jmp qword ptr [rbp + 0]
// 41 FF 24 24	| jmp qword ptr [r12]
// 41 FF 65 00	| jmp qword ptr [r13 + 0]
// 41 FF 26			| jmp qword ptr [r14]
// 41 FF 27			| jmp qword ptr [r15]

namespace horizon::memory
{

extern "C"
{

	// 
	// secure call assembly code
	// 
	void* code_secure_call();

}; // extern "C"

struct ArgData
{
	ArgData( std::uintptr_t jmp, std::uintptr_t procedure )
		: m_jmp( jmp )
		, m_procedure( procedure )
		, m_register( 0 )
	{ }

	std::uintptr_t m_jmp = 0;				// address of jump gadget
	std::uintptr_t m_procedure = 0;	// address of function
	std::uintptr_t m_register = 0;	// value of gadget register
};

template< typename ReturnType, typename... ArgPack >
ReturnType SecureCall( std::uintptr_t gadget, std::uintptr_t procedure, ArgPack... arg_pack )
{
	ArgData arg_data( gadget, procedure );

	using ArgMap = ArgStack< sizeof...( ArgPack ), void >;
	return ArgMap::template Call< ReturnType >( &code_secure_call, &arg_data, arg_pack... );
}

template< typename ReturnType, typename... ArgPack >
ReturnType SecureCall( std::uintptr_t procedure, ArgPack... arg_pack )
{
	static std::uintptr_t gadget = 0;

	if( !memory::IsAddressValid( gadget ) )
	{
		const auto game_assembly = win32::GetImage( HASH( L"GameAssembly.dll" ) );

		if( memory::IsAddressValid( game_assembly ) )
		{
			gadget = memory::ScanImageSection( game_assembly, HASH( ".text" ), SECURE( "FF E7" ) );
		}
		else
		{
			gadget = memory::ScanSection( HASH( ".text" ), SECURE( "FF E7" ) );
		}
	}

	return SecureCall< ReturnType, ArgPack... >( gadget, procedure, arg_pack... );
}

template< std::size_t Index, typename ReturnType, typename... ArgPack >
ReturnType SecureCallVirtual( void* instance, ArgPack... arg_pack )
{
	const auto procedure_array = Dereference< std::uintptr_t* >( instance );
	return SecureCall< ReturnType >( procedure_array[ Index ], instance, arg_pack... );
}

template< typename Type, typename... ArgPack >
class WrapSecureCall
{
public:
	FORCEINLINE WrapSecureCall( std::uintptr_t address = 0 )
		: m_address( address )
	{ }

public:
	FORCEINLINE bool IsValid() const
	{
		return ( m_address != 0 );
	}

	FORCEINLINE std::uintptr_t Get() const
	{
		return m_address;
	}

	FORCEINLINE void Set( std::uintptr_t base )
	{
		m_address += base;
	}

public:
	FORCEINLINE Type operator()( ArgPack... arg_pack )
	{
		return SecureCall< Type >( m_address, arg_pack... );
	}

public:
	FORCEINLINE explicit operator std::uintptr_t() const
	{
		return m_address;
	}

protected:
	std::uintptr_t m_address = 0;		// 0x0000
};
// sizeof( WrapSecureCall ) = 0x0008

} // namespace horizon::memory