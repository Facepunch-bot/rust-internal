#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

namespace horizon::memory
{

template< typename ReturnType, typename... ArgPack >
ReturnType ExecuteCall( const void* const code, ArgPack... arg_pack )
{
	const auto procedure = static_cast< ReturnType( * )( ArgPack... ) >( code );
	return procedure( arg_pack... );
}

template< std::size_t ArgCount, typename >
struct ArgStack
{
	template< typename T1, typename T2, typename T3, typename T4, typename... ArgPack >
	static std::uintptr_t SystemCall( const void* const code,
																		std::uint32_t system_number,
																		T1 arg1, T2 arg2, T3 arg3, T4 arg4,
																		ArgPack... arg_pack )
	{
		return ExecuteCall< std::uintptr_t >( code, arg1, arg2, arg3, arg4, system_number, nullptr, arg_pack... );
	}

	template< typename ReturnType, typename T1, typename T2, typename T3, typename T4, typename... ArgPack >
	static ReturnType Call( const void* const code,
													void* const arg_data,
													T1 arg1, T2 arg2, T3 arg3, T4 arg4,
													ArgPack... arg_pack )
	{
		return ExecuteCall< ReturnType >( code, arg1, arg2, arg3, arg4, arg_data, nullptr, arg_pack... );
	}
};

template< std::size_t ArgCount >
struct ArgStack< ArgCount, std::enable_if_t< ArgCount <= 4 > >
{
	template< typename T1 = void*, typename T2 = void*, typename T3 = void*, typename T4 = void* >
	static std::uintptr_t SystemCall( const void* const code,
																		std::uint32_t system_number,
																		T1 arg1 = { }, T2 arg2 = { }, T3 arg3 = { }, T4 arg4 = { } )
	{
		return ExecuteCall< std::uintptr_t >( code, arg1, arg2, arg3, arg4, system_number, nullptr );
	}

	template< typename ReturnType, typename T1 = void*, typename T2 = void*, typename T3 = void*, typename T4 = void* >
	static ReturnType Call( const void* const code,
													void* const arg_data,
													T1 arg1 = { }, T2 arg2 = { }, T3 arg3 = { }, T4 arg4 = { } )
	{
		return ExecuteCall< ReturnType >( code, arg1, arg2, arg3, arg4, arg_data, nullptr );
	}
};

} // namespace horizon::memory