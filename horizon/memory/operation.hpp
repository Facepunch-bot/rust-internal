#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#define PAGE_SIZE		( 4096 )

namespace horizon::memory
{

constexpr std::uintptr_t MinimumUserAddress = 0x0000000000010000;
constexpr std::uintptr_t MaximumUserAddress = 0x00007FFFFFFFFFFF;

constexpr std::uintptr_t MinimumSystemAddress = 0x8000000000000000;

inline std::uintptr_t ToAddress( const void* pointer )
{
	return reinterpret_cast< std::uintptr_t >( pointer );
}

inline void* ToPointer( std::uintptr_t address )
{
	return reinterpret_cast< void* >( address );
}

inline const void* ToConstantPointer( std::uintptr_t address )
{
	return reinterpret_cast< const void* >( address );
}

inline bool IsUserAddress( std::uintptr_t address )
{
	return ( address >= MinimumUserAddress &&
					 address <= MaximumUserAddress );
}

inline bool IsUserAddress( const void* pointer )
{
	const auto address = ToAddress( pointer );
	return IsUserAddress( address );
}

inline bool IsSystemAddress( std::uintptr_t address )
{
	return ( address >= MinimumSystemAddress );
}

inline bool IsSystemAddress( const void* pointer )
{
	const auto address = ToAddress( pointer );
	return IsSystemAddress( address );
}

inline bool IsAddressValid( std::uintptr_t address )
{
	return IsUserAddress( address );
}

inline bool IsAddressValid( const void* pointer )
{
	const auto address = ToAddress( pointer );
	return IsAddressValid( address );
}

template< typename Type, typename PointerType >
inline Type& Dereference( const PointerType address )
{
	return *( Type* )( address );
}

template< typename Type, typename PointerType >
inline Type Read( const PointerType address )
{
	return Dereference< Type, PointerType >( address );
}

template< typename Type, typename PointerType >
inline Type& Write( const PointerType address, const Type& data )
{
	return Dereference< Type, PointerType >( address ) = data;
}

template< std::size_t N, typename T = std::uintptr_t >
FORCEINLINE T GetVirtualAddress( void* object )
{
	if( !IsAddressValid( object ) )
		return { };

	const auto procedure_array = *reinterpret_cast< std::uintptr_t** >( object );

	if( !IsAddressValid( procedure_array ) )
		return { };

	return T( procedure_array[ N ] );
}

template< std::size_t N, typename T, typename... ArgPack >
FORCEINLINE T CallVirtual( void* object, ArgPack... arg_pack )
{
	using Fn = T( API_THISCALL* )( void*, ArgPack... );

	const auto procedure = GetVirtualAddress< N, Fn >( object );

	if( !procedure )
	{
		return std::invoke_result_t< Fn, void*, ArgPack... >();
	}

	return procedure( object, arg_pack... );
}

template< typename T, typename... ArgPack >
FORCEINLINE T Call( std::uintptr_t address, ArgPack... arg_pack )
{
	using Fn = T( * )( ArgPack... );
	const auto procedure = reinterpret_cast< Fn >( address );

	if( !IsAddressValid( procedure ) )
	{
		return std::invoke_result_t< Fn, ArgPack... >();
	}

	return procedure( arg_pack... );
}

template< typename Type >
inline void SafeDelete( Type& object )
{
	if( IsAddressValid( object ) )
	{
		delete object;
		object = nullptr;
	}
}

template< typename Type >
inline void SafeDeleteArray( Type& object )
{
	if( IsAddressValid( object ) )
	{
		delete[] object;
		object = nullptr;
	}
}

template< typename Type >
inline void SafeRelease( Type& object )
{
	if( IsAddressValid( object ) )
	{
		object->Release();
		object = nullptr;
	}
}

} // namespace horizon::memory