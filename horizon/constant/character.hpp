#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

namespace horizon::constant
{

template< typename Type >
constexpr bool IsTerminator( const Type character )
{
	return ( character == static_cast< const Type >( 0 ) );
}

template< typename Type >
constexpr bool IsSpace( const Type character )
{
	return ( character == static_cast< const Type >( 32 ) );
}

template< typename Type >
constexpr bool IsQuestion( const Type character )
{
	return ( character == static_cast< const Type >( 63 ) );
}

template< typename Type >
constexpr bool IsDecimal( const Type character )
{
	return ( character >= static_cast< const Type >( 48 ) &&
					 character <= static_cast< const Type >( 57 ) );
}

template< typename Type >
constexpr bool IsLower( const Type character )
{
	return ( character >= static_cast< const Type >( 97 ) &&
					 character <= static_cast< const Type >( 122 ) );
}

template< typename Type >
constexpr bool IsUpper( const Type character )
{
	return ( character >= static_cast< const Type >( 65 ) &&
					 character <= static_cast< const Type >( 90 ) );
}

template< typename Type >
constexpr Type ToLower( const Type character )
{
	if( IsUpper( character ) )
	{
		return ( character + static_cast< const Type >( 32 ) );
	}

	return character;
}

template< typename Type >
constexpr Type ToUpper( const Type character )
{
	if( IsLower( character ) )
	{
		return ( character - static_cast< const Type >( 32 ) );
	}

	return character;
}

} // namespace horizon::constant