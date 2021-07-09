#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

namespace horizon::memory
{

std::uintptr_t ScanRegionInternal( const std::uint8_t* region_begin, const std::uint8_t* region_end, const char* signature );
std::uintptr_t ScanImageSectionInternal( std::uintptr_t image, const char* const section_name, const char* const signature );
std::uintptr_t ScanImageSectionInternal( std::uintptr_t image, std::uint64_t section_name_hash, const char* const signature );
std::uintptr_t ScanImageInternal( std::uintptr_t image, const char* signature );
std::uintptr_t ScanSectionInternal( std::uint64_t name_hash, const char* signature );
std::uintptr_t ScanInternal( const char* signature );

std::uintptr_t GetAbsoluteAddressInternal( std::uintptr_t address, std::size_t opcode_count );

template< typename Type = std::uintptr_t >
FORCEINLINE Type ScanRegion( const std::uint8_t* region_begin, const std::uint8_t* region_end, const char* signature )
{
	return Type( ScanRegionInternal( region_begin, region_end, signature ) );
}

template< typename Type = std::uintptr_t >
FORCEINLINE Type ScanImageSection( std::uintptr_t image, const char* const section_name, const char* const signature )
{
	return Type( ScanImageSectionInternal( image, section_name, signature ) );
}

template< typename Type = std::uintptr_t >
FORCEINLINE Type ScanImageSection( std::uintptr_t image, std::uint64_t section_name_hash, const char* const signature )
{
	return Type( ScanImageSectionInternal( image, section_name_hash, signature ) );
}

template< typename Type = std::uintptr_t >
FORCEINLINE Type ScanImage( std::uintptr_t image, const char* signature )
{
	return Type( ScanImageInternal( image, signature ) );
}

template< typename Type = std::uintptr_t >
FORCEINLINE Type ScanSection( std::uint64_t name_hash, const char* const signature )
{
	return Type( ScanSectionInternal( name_hash, signature ) );
}

template< typename Type = std::uintptr_t >
FORCEINLINE Type Scan( const char* signature )
{
	return Type( ScanInternal( signature ) );
}

template< typename Type = std::uintptr_t >
FORCEINLINE Type GetAbsoluteAddress( std::uintptr_t address, std::size_t opcode_count )
{
	return Type( GetAbsoluteAddressInternal( address, opcode_count ) );
}

} // namespace horizon::memory