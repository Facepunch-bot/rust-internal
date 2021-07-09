#include "memory.hpp"

#pragma function( memchr )
const void* memchr( const void* destination, int value, std::size_t size )
{
	auto data = static_cast< const std::uint8_t* >( destination );

	for( std::size_t index = 0; index < size; index++ )
	{
		if( data[ index ] == static_cast< const std::uint8_t >( value ) )
		{
			return static_cast< const void* >( data );
		}
	}

	return nullptr;
}

#pragma function( memcmp )
int memcmp( const void* source, const void* destination, std::size_t size )
{
	auto data_source = static_cast< const std::uint8_t* >( source );
	auto data_destination = static_cast< const std::uint8_t* >( destination );

	for( std::size_t index = 0; index < size; index++ )
	{
		if( data_source[ index ] != data_destination[ index ] )
		{
			return ( data_source[ index ] - data_destination[ index ] );
		}
	}

	return 0;
}

#pragma function( memcpy )
void* memcpy( void* destination, const void* source, std::size_t size )
{
	auto data_source = static_cast< const std::uint8_t* >( source );
	auto data_destination = static_cast< std::uint8_t* >( destination );

	__movsb( data_destination, data_source, size );
	return static_cast< void* >( data_destination );
}

#pragma function( memmove )
void* memmove( void* destination, const void* source, std::size_t size )
{
	auto data_source = static_cast< const std::uint8_t* >( source );
	auto data_destination = static_cast< std::uint8_t* >( destination );

	__movsb( data_destination, data_source, size );
	return static_cast< void* >( data_destination );
}

#pragma function( memset )
void* memset( void* destination, int value, std::size_t size )
{
	auto data = static_cast< std::uint8_t* >( destination );

	__stosb( data, static_cast< std::uint8_t >( value ), size );
	return static_cast< void* >( data );
}