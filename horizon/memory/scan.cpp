#include "scan.hpp"
#include "operation.hpp"

#include "../constant/hash.hpp"
#include "../constant/string.hpp"

#include "../win32/trace.hpp"
#include "../win32/image.hpp"

#define IN_RANGE( x, a, b )	( x >= a && x <= b )
#define GET_BITS( x )		( IN_RANGE( x, '0', '9' ) ? ( x - '0' ) : ( ( x & ( ~0x20 ) ) - 'A' + 0x0A ) )
#define GET_BYTE( x )		( GET_BITS( x[ 0 ] ) << 4 | GET_BITS( x[ 1 ] ) )

namespace horizon::memory
{

std::uintptr_t ScanRegionInternal( const std::uint8_t* region_begin, const std::uint8_t* region_end, const char* signature )
{
	if( !IsAddressValid( region_begin ) )
	{
		return 0;
	}
	
	if( !IsAddressValid( region_end ) )
	{
		return 0;
	}
	
	if( !IsAddressValid( signature ) )
	{
		return 0;
	}

	auto scan_result = static_cast< std::uintptr_t >( 0 );
	auto scan_compare = reinterpret_cast< const std::uint8_t* >( signature );

	const auto scan_begin = region_begin;
	const auto scan_end = region_end;

	for( auto scan_current = scan_begin; scan_current < scan_end; scan_current++ )
	{
		if( constant::IsTerminator( scan_compare[ 0 ] ) )
		{
			return scan_result;
		}

		if( IsAddressValid( const_cast< std::uint8_t* >( scan_current ) ) )
		{
			if( constant::IsQuestion( scan_compare[ 0 ] ) || scan_current[ 0 ] == GET_BYTE( scan_compare ) )
			{
				if( !memory::IsAddressValid( scan_result ) )
				{
					scan_result = ToAddress( scan_current );
				}

				if( constant::IsTerminator( scan_compare[ 2 ] ) )
				{
					return scan_result;
				}

				const bool question[ 2 ] =
				{
					constant::IsQuestion( scan_compare[ 0 ] ),
					constant::IsQuestion( scan_compare[ 1 ] ),
				};

				if( ( question[ 0 ] && question[ 1 ] ) || ( !question[ 0 ] ) )
				{
					scan_compare = ( scan_compare + 3 );
				}
				else
				{
					scan_compare = ( scan_compare + 2 );
				}
			}
			else
			{
				scan_compare = reinterpret_cast< const std::uint8_t* >( signature );
				scan_result = 0;
			}
		}
	}

	return 0;
}

std::uintptr_t ScanImageSectionInternal( std::uintptr_t image, const char* const name, const char* const signature )
{
	if( memory::IsAddressValid( name ) )
	{
		std::size_t section_size = 0;
		const auto section_begin = win32::GetImageSection< const std::uint8_t* >( image, name, &section_size );

		if( memory::IsAddressValid( section_begin ) )
		{
			const auto section_end = ( section_begin + section_size );
			return ScanRegionInternal( section_begin, section_end, signature );
		}
	}

	return 0;
}

std::uintptr_t ScanImageSectionInternal( std::uintptr_t image, std::uint64_t hash, const char* const signature )
{
	if( hash )
	{
		std::size_t section_size = 0;
		const auto section_begin = win32::GetImageSection< const std::uint8_t* >( image, hash, &section_size );

		if( memory::IsAddressValid( section_begin ) )
		{
			const auto section_end = ( section_begin + section_size );
			return ScanRegionInternal( section_begin, section_end, signature );
		}
	}

	return 0;
}

std::uintptr_t ScanImageInternal( std::uintptr_t image, const char* signature )
{
	const auto image_nt_headers = win32::GetImageNtHeaders( image );

	if( !IsAddressValid( image_nt_headers ) )
	{
		return 0;
	}

	const auto region_begin = reinterpret_cast< const std::uint8_t* >( image );
	const auto region_end = reinterpret_cast< const std::uint8_t* >( image + image_nt_headers->OptionalHeader.SizeOfImage );

	return ScanRegionInternal( region_begin, region_end, signature );
}

std::uintptr_t ScanSectionInternal( std::uint64_t name_hash, const char* signature )
{
	const auto image = win32::GetImage( nullptr );

	if( memory::IsAddressValid( image ) )
	{
		return ScanImageSectionInternal( image, name_hash, signature );
	}

	return 0;
}

std::uintptr_t ScanInternal( const char* signature )
{
	const auto image = win32::GetImage( nullptr );

	if( !IsAddressValid( image ) )
	{
		return 0;
	}

	return ScanImageInternal( image, signature );
}

std::uintptr_t GetAbsoluteAddressInternal( std::uintptr_t address, std::size_t opcode_count )
{
	if( !IsAddressValid( address ) )
	{
		return 0;
	}

	const auto disp = *reinterpret_cast< std::int32_t* >( address + opcode_count );

	if( disp == 0 )
	{
		return 0;
	}

	return ( address + opcode_count + disp + sizeof( disp ) );
}

}