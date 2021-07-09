#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "secure_call.hpp"

namespace horizon::memory
{

extern "C"
{

	void* code_system_call();

}; // extern "C"

constexpr std::uint32_t BadSystemNumber = std::numeric_limits< std::uint32_t >::max();

template< typename ReturnType, typename... ArgPack >
ReturnType SystemCall( std::uint32_t system_number, ArgPack... arg_pack )
{
	using ArgMap = ArgStack< sizeof...( ArgPack ), void >;
	const auto return_value = ArgMap::template SystemCall( &code_system_call, system_number, arg_pack... );
	return static_cast< ReturnType >( return_value );
}

template< typename Type, typename... ArgPack >
class WrapSystemCall
{
public:
	FORCEINLINE WrapSystemCall( std::uint32_t number = BadSystemNumber )
		: m_number( number )
	{ }

public:
	FORCEINLINE bool IsValid() const
	{
		return ( m_number != BadSystemNumber );
	}

	FORCEINLINE std::uint32_t GetNumber() const
	{
		return m_number;
	}

	FORCEINLINE void SetNumber( std::uint32_t number )
	{
		m_number = number;
	}

public:
	FORCEINLINE Type operator()( ArgPack... arg_pack ) const
	{
		return SystemCall< Type >( m_number, arg_pack... );
	}

protected:
	std::uint32_t m_number = BadSystemNumber;	// 0x0000
};
// sizeof( WrapSystemCall ) = 0x0004

} // namespace horizon::memory