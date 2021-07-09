#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "../constant/character.hpp"
#include "../constant/hash.hpp"
#include "../constant/string.hpp"

#include "../memory/operation.hpp"

#include "sdk/list_entry.hpp"

#include "sdk/string.hpp"
#include "sdk/unicode_string.hpp"

#include "sdk/image_base_relocation.hpp"
#include "sdk/image_data_directory.hpp"
#include "sdk/image_dos_header.hpp"
#include "sdk/image_export_directory.hpp"
#include "sdk/image_file_header.hpp"
#include "sdk/image_import_by_name.hpp"
#include "sdk/image_import_descriptor.hpp"
#include "sdk/image_nt_headers.hpp"
#include "sdk/image_optional_header.hpp"
#include "sdk/image_relocation.hpp"
#include "sdk/image_runtime_function_entry.hpp"
#include "sdk/image_section_header.hpp"
#include "sdk/image_thunk_data.hpp"

#include "sdk/ldr_data_table_entry.hpp"

namespace horizon::win32
{

IMAGE_DOS_HEADER* GetImageDosHeader( std::uintptr_t image );
IMAGE_NT_HEADERS* GetImageNtHeaders( std::uintptr_t image );

IMAGE_DATA_DIRECTORY* GetImageDataDirectory( std::uintptr_t image, std::uint16_t directory );

template< typename Type = std::uintptr_t >
Type GetImageDataDirectory( std::uintptr_t image, std::uint16_t directory, std::size_t* size = nullptr )
{
	const auto image_data_directory = GetImageDataDirectory( image, directory );

	if( memory::IsAddressValid( image_data_directory ) )
	{
		if( memory::IsAddressValid( size ) )
		{
			( *size ) = static_cast< std::size_t >( image_data_directory->Size );
		}

		if( image_data_directory->VirtualAddress )
		{
			return Type( image + image_data_directory->VirtualAddress );
		}
	}

	return { };
}

IMAGE_SECTION_HEADER* GetImageSectionHeader( std::uintptr_t image, std::size_t* size = nullptr );

struct ImageParameters
{
	std::uint64_t m_hash = 0;		// 0x0000
	std::uintptr_t m_base = 0;	// 0x0008
	std::size_t m_size = 0;			// 0x0010
};
// sizeof( ImageParameters ) = 0x0018

struct SectionParameters
{
	std::uint64_t m_hash = 0;		// 0x0000
	std::uint32_t m_base = 0;		// 0x0008
	std::uint32_t m_size = 0;		// 0x000C
};
// sizeof( SectionParameters ) = 0x0010

struct ExportParameters
{
	std::uint64_t m_hash = 0;			// 0x0000
	std::uint16_t m_ordinal = 0;	// 0x0008
	std::uintptr_t m_address = 0;	// 0x0010
};
// sizeof( ExportParameters ) = 0x0018

using OnImageEntryFn = bool( * )( ImageParameters* parameters, LDR_DATA_TABLE_ENTRY* entry );
using OnImageSectionFn = bool( * )( SectionParameters* parameters, IMAGE_SECTION_HEADER* section );
using OnImageExportFn = bool( * )( ExportParameters* parameters, std::uintptr_t address, std::uint16_t ordinal, const char* const name );

bool EnumerateImages( OnImageEntryFn enumerate, ImageParameters* parameters = nullptr );
bool EnumerateImageSections( std::uintptr_t image, OnImageSectionFn enumerate, SectionParameters* parameters = nullptr );
bool EnumerateImageExports( std::uintptr_t image, OnImageExportFn enumerate, ExportParameters* parameters = nullptr );

template< typename Type = std::uintptr_t >
Type GetImage( std::uint64_t hash, std::size_t* size = nullptr )
{
	auto enumerate = []( ImageParameters* parameters, LDR_DATA_TABLE_ENTRY* entry )
	{
		if( memory::IsAddressValid( parameters ) )
		{
			if( parameters->m_hash )
			{
				const auto& base_name = entry->BaseDllName;

				if( base_name.Length )
				{
					if( constant::Hash( base_name, true ) == parameters->m_hash )
					{
						parameters->m_base = memory::ToAddress( entry->DllBase );
						parameters->m_size = static_cast< std::size_t >( entry->SizeOfImage );
						return true;
					}
				}
			}
			else
			{
				parameters->m_base = memory::ToAddress( entry->DllBase );
				parameters->m_size = static_cast< std::size_t >( entry->SizeOfImage );
				return true;
			}
		}

		return false;
	};

	ImageParameters parameters = { };
	parameters.m_hash = hash;

	if( EnumerateImages( enumerate, &parameters ) )
	{
		if( memory::IsAddressValid( size ) )
		{
			( *size ) = parameters.m_size;
		}

		return Type( parameters.m_base );
	}

	return { };
}

template< typename Type = std::uintptr_t >
Type GetImage( const wchar_t* const name, std::size_t* size = nullptr )
{
	std::uint64_t hash = 0;

	if( memory::IsAddressValid( name ) )
	{
		hash = constant::Hash( name, true );
	}

	return GetImage< Type >( hash, size );
}

template< typename Type = std::uintptr_t >
Type GetImageSection( std::uintptr_t image, std::uint64_t hash, std::size_t* size = nullptr )
{
	auto enumerate = []( SectionParameters* parameters, IMAGE_SECTION_HEADER* section )
	{
		if( memory::IsAddressValid( parameters ) )
		{
			char section_name[ 16 ] = { };
			std::memcpy( section_name, section->Name, sizeof( section->Name ) );

			if( constant::Hash( section_name, true ) == parameters->m_hash )
			{
				parameters->m_base = section->VirtualAddress;
				parameters->m_size = section->Misc.VirtualSize;
				return true;
			}
		}

		return false;
	};

	SectionParameters parameters = { };
	parameters.m_hash = hash;

	if( EnumerateImageSections( image, enumerate, &parameters ) )
	{
		if( memory::IsAddressValid( size ) )
		{
			( *size ) = static_cast< std::size_t >( parameters.m_size );
		}

		if( parameters.m_base )
		{
			return Type( image + parameters.m_base );
		}
	}

	return { };
}

template< typename Type = std::uintptr_t >
Type GetImageSection( std::uintptr_t image, const char* const name, std::size_t* size = nullptr )
{
	if( memory::IsAddressValid( name ) )
	{
		const auto hash = constant::Hash( name, true );
		return GetImageSection< Type >( image, hash, size );
	}

	return { };
}

template< typename Type = std::uintptr_t >
Type GetImageExport( std::uintptr_t image, std::uint64_t hash )
{
	auto enumerate = []( ExportParameters* parameters, std::uintptr_t address, std::uint16_t ordinal, const char* const name )
	{
		if( memory::IsAddressValid( parameters ) )
		{
			const auto hash = constant::Hash( name, true );

			if( hash == parameters->m_hash )
			{
				parameters->m_address = address;
				parameters->m_ordinal = ordinal;
				return true;
			}
		}

		return false;
	};

	ExportParameters parameters = { };
	parameters.m_hash = hash;

	if( EnumerateImageExports( image, enumerate, &parameters ) )
	{
		return Type( parameters.m_address );
	}

	return { };
}

template< typename Type = std::uintptr_t >
Type GetImageExport( std::uintptr_t image, const char* const name )
{
	if( memory::IsAddressValid( name ) )
	{
		const auto hash = constant::Hash( name, true );
		return GetImageExport< Type >( image, hash );
	}

	return { };
}

const LDR_DATA_TABLE_ENTRY* GetLdrDataTableEntry( const LIST_ENTRY* list_head, const wchar_t* const name );
const LDR_DATA_TABLE_ENTRY* GetLdrDataTableEntry( const LIST_ENTRY* list_head, std::uint64_t name_hash );

} // namespace horizon::win32