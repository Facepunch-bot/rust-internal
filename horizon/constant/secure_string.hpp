#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "character.hpp"
#include "hash.hpp"
#include "string.hpp"

namespace horizon::constant
{

template< typename Type >
using WrapType = typename std::remove_const_t< std::remove_reference_t< Type > >;

template< std::size_t Size, char Key1, char Key2, typename Type >
class SecureString
{
public:
	FORCEINLINE constexpr SecureString( Type* data )
	{
		compute( data );
	}

	FORCEINLINE Type* get()
	{
		return m_storage;
	}

	FORCEINLINE std::size_t size() const
	{
		return Size;
	}

	FORCEINLINE std::size_t size_in_bytes() const
	{
		return ( Size * sizeof( Type ) );
	}

	FORCEINLINE std::size_t length() const
	{
		return ( Size - 1 );
	}

	FORCEINLINE char get_key() const
	{
		return Key1;
	}

	FORCEINLINE bool is_decrypted() const
	{
		const auto index = length();
		return IsTerminator( m_storage[ index ] );
	}

	FORCEINLINE bool is_encrypted() const
	{
		return !( is_decrypted() );
	}

	FORCEINLINE Type* encrypt()
	{
		if( is_decrypted() )
		{
			compute( m_storage );
		}

		return m_storage;
	}

	FORCEINLINE Type* decrypt()
	{
		if( is_encrypted() )
		{
			compute( m_storage );
		}

		return m_storage;
	}

	FORCEINLINE void clear()
	{
		for( std::size_t index = 0; index < Size; index++ )
		{
			m_storage[ index ] = static_cast< Type >( 0 );
		}
	}

protected:
	FORCEINLINE constexpr void compute( Type* data )
	{
		for( std::size_t index = 0; index < Size; index++ )
		{
			m_storage[ index ] = static_cast< Type >( data[ index ] ^ ( Key1 + index % ( 1 + Key2 ) ) );
		}
	}

protected:
	Type m_storage[ Size ] = { };
};

} // namespace horizon::constant

#define SECURE_STRING_IMPL( name, data )	\
	static constexpr auto name = horizon::constant::SecureString				\
		< sizeof( data ) / sizeof( data[ 0 ] ),														\
			__TIME__[ 4 ],																									\
			__TIME__[ 7 ],																									\
			horizon::constant::WrapType< decltype( data[ 0 ] ) > >					\
		( ( horizon::constant::WrapType< decltype( data[ 0 ] ) >* )data )

#define SECURE_STRING( data )						\
	[]()																	\
	{																			\
		SECURE_STRING_IMPL( result, data );	\
		return result;											\
	}()

#define SECURE( data )									\
	[]()																	\
	{																			\
		SECURE_STRING_IMPL( result, data );	\
		return result;											\
	}().decrypt()