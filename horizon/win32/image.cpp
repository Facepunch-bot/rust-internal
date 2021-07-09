#include "image.hpp"
#include "string.hpp"
#include "process.hpp"

#include "../constant/hash.hpp"

#include "../memory/operation.hpp"

#include "../win32/trace.hpp"

namespace horizon::win32
{

IMAGE_DOS_HEADER* GetImageDosHeader( std::uintptr_t image )
{
	if( memory::IsAddressValid( image ) )
	{
		const auto image_dos_header = reinterpret_cast< IMAGE_DOS_HEADER* >( image );

		if( image_dos_header->e_magic == IMAGE_DOS_SIGNATURE )
		{
			return image_dos_header;
		}
	}

	return nullptr;
}

IMAGE_NT_HEADERS* GetImageNtHeaders( std::uintptr_t image )
{
	const auto image_dos_header = GetImageDosHeader( image );

	if( memory::IsAddressValid( image_dos_header ) )
	{
		const auto image_nt_headers = reinterpret_cast< IMAGE_NT_HEADERS* >( image + image_dos_header->e_lfanew );

		if( image_nt_headers->Signature == IMAGE_NT_SIGNATURE )
		{
			return image_nt_headers;
		}
	}

	return nullptr;
}

IMAGE_DATA_DIRECTORY* GetImageDataDirectory( std::uintptr_t image, std::uint16_t directory )
{
	if( directory < IMAGE_NUMBEROF_DIRECTORY_ENTRIES )
	{
		const auto image_nt_headers = GetImageNtHeaders( image );

		if( memory::IsAddressValid( image_nt_headers ) )
		{
			return &image_nt_headers->OptionalHeader.DataDirectory[ directory ];
		}
	}

	return nullptr;
}

IMAGE_SECTION_HEADER* GetImageSectionHeader( std::uintptr_t image, std::size_t* size /*= nullptr*/ )
{
	const auto image_nt_headers = GetImageNtHeaders( image );

	if( memory::IsAddressValid( image_nt_headers ) )
	{
		const auto image_file_header = &image_nt_headers->FileHeader;
		const auto image_optional_header = &image_nt_headers->OptionalHeader;

		if( memory::IsAddressValid( size ) )
		{
			( *size ) = static_cast< std::size_t >( image_file_header->NumberOfSections );
		}

		if( image_file_header->NumberOfSections )
		{
			const auto image_section_header = ( memory::ToAddress( image_optional_header ) + image_file_header->SizeOfOptionalHeader );
			return reinterpret_cast< IMAGE_SECTION_HEADER* >( image_section_header );
		}
	}

	return nullptr;
}

bool EnumerateImages( OnImageEntryFn enumerate, ImageParameters* parameters /*= nullptr*/ )
{
	if( memory::IsAddressValid( enumerate ) )
	{
		const auto peb = NtCurrentPeb();

		if( memory::IsAddressValid( peb ) )
		{
			const auto peb_ldr_data = peb->Ldr;

			if( memory::IsAddressValid( peb_ldr_data ) )
			{
				const auto list_head = &peb_ldr_data->InLoadOrderModuleList;

				for( auto list_entry = list_head->Flink; list_entry != list_head; list_entry = list_entry->Flink )
				{
					const auto entry = CONTAINING_RECORD( list_entry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks );

					if( memory::IsAddressValid( entry ) )
					{
						if( enumerate( parameters, entry ) )
						{
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

bool EnumerateImageSections( std::uintptr_t image, OnImageSectionFn enumerate, SectionParameters* parameters /*= nullptr*/ )
{
	if( memory::IsAddressValid( enumerate ) )
	{
		std::size_t image_section_header_size = 0;
		const auto image_section_header = GetImageSectionHeader( image, &image_section_header_size );

		if( memory::IsAddressValid( image_section_header ) )
		{
			for( std::size_t index = 0; index < image_section_header_size; index++ )
			{
				const auto section = &image_section_header[ index ];

				if( memory::IsAddressValid( section ) )
				{
					if( enumerate( parameters, section ) )
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool EnumerateImageExports( std::uintptr_t image, OnImageExportFn enumerate, ExportParameters* parameters /*= nullptr*/ )
{
	if( memory::IsAddressValid( enumerate ) )
	{
		std::size_t image_export_directory_size = 0;
		const auto image_export_directory = GetImageDataDirectory< IMAGE_EXPORT_DIRECTORY* >( image, IMAGE_DIRECTORY_ENTRY_EXPORT,
																																													&image_export_directory_size );

		if( memory::IsAddressValid( image_export_directory ) )
		{
			if( image_export_directory->AddressOfFunctions &&
					image_export_directory->AddressOfNames &&
					image_export_directory->AddressOfNameOrdinals )
			{
				const auto functions = reinterpret_cast< const std::uint32_t* >( image + image_export_directory->AddressOfFunctions );
				const auto names = reinterpret_cast< const std::uint32_t* >( image + image_export_directory->AddressOfNames );
				const auto ordinals = reinterpret_cast< const std::uint16_t* >( image + image_export_directory->AddressOfNameOrdinals );

				for( std::uint32_t index = 0; index < image_export_directory->NumberOfNames; index++ )
				{
					const auto ordinal = ordinals[ index ];
					const auto displacement = functions[ ordinal ];

					if( displacement )
					{
						const auto address = ( image + displacement );
						const auto name_displacement = names[ index ];

						if( name_displacement )
						{
							const auto name = reinterpret_cast< const char* >( image + name_displacement );

							if( enumerate( parameters, address, ordinal, name ) )
							{
								return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}

const LDR_DATA_TABLE_ENTRY* GetLdrDataTableEntry( const LIST_ENTRY* list_head, const wchar_t* const name )
{
	for( auto list_entry = list_head->Flink; list_entry != list_head; list_entry = list_entry->Flink )
	{
		const auto ldr_data_table_entry = CONTAINING_RECORD( list_entry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks );

		if( memory::IsAddressValid( ldr_data_table_entry ) )
		{
			const auto& base_name = ldr_data_table_entry->BaseDllName;

			if( constant::AreEqual( base_name, name, true ) )
			{
				return ldr_data_table_entry;
			}
		}
	}

	return nullptr;
}

const LDR_DATA_TABLE_ENTRY* GetLdrDataTableEntry( const LIST_ENTRY* list_head, std::uint64_t name_hash )
{
	for( auto list_entry = list_head->Flink; list_entry != list_head; list_entry = list_entry->Flink )
	{
		const auto ldr_data_table_entry = CONTAINING_RECORD( list_entry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks );

		if( memory::IsAddressValid( ldr_data_table_entry ) )
		{
			const auto& base_name = ldr_data_table_entry->BaseDllName;

			if( base_name.Length > 0 )
			{
				if( constant::Hash( base_name, true ) == name_hash )
				{
					return ldr_data_table_entry;
				}
			}
		}
	}

	return nullptr;
}

/*
std::uintptr_t GetImageExport( std::uintptr_t image, const char* const name )
{
	if( !memory::IsAddressValid( name ) )
	{
		return 0;
	}

	const auto name_length = constant::GetLength( name );

	if( name_length <= 1 )
	{
		return 0;
	}

	const auto image_data_directory = GetImageDataDirectory( image, IMAGE_DIRECTORY_ENTRY_EXPORT );

	if( !memory::IsAddressValid( image_data_directory ) )
	{
		return 0;
	}

	const auto image_export_directory = reinterpret_cast< const IMAGE_EXPORT_DIRECTORY* >( image + image_data_directory->VirtualAddress );

	if( !memory::IsAddressValid( image_export_directory ) )
	{
		return 0;
	}

	if( !image_export_directory->Base ||
			!image_export_directory->AddressOfFunctions ||
			!image_export_directory->AddressOfNames ||
			!image_export_directory->AddressOfNameOrdinals ||
			!image_export_directory->NumberOfFunctions ||
			!image_export_directory->NumberOfNames )
	{
		return 0;
	}

	const auto functions = reinterpret_cast< const std::uint32_t* >( image + image_export_directory->AddressOfFunctions );
	const auto names = reinterpret_cast< const std::uint32_t* >( image + image_export_directory->AddressOfNames );
	const auto name_ordinals = reinterpret_cast< const std::uint16_t* >( image + image_export_directory->AddressOfNameOrdinals );

	for( auto index = 0ul; index < image_export_directory->NumberOfFunctions; index++ )
	{
		const auto export_ordinal = name_ordinals[ index ];
		const auto export_procedure = functions[ export_ordinal ];

		if( export_procedure )
		{
			const auto export_name = reinterpret_cast< const char* >( image + names[ index ] );

			if( memory::IsAddressValid( export_name ) )
			{
				if( constant::AreEqual( export_name, name, name_length, true ) )
				{
					return ( image + export_procedure );
				}
			}
		}
	}

	return 0;
}

std::uintptr_t GetImageExport( std::uintptr_t image, std::uint64_t name_hash )
{
	if( !name_hash )
	{
		return 0;
	}

	const auto image_data_directory = GetImageDataDirectory( image, IMAGE_DIRECTORY_ENTRY_EXPORT );

	if( !memory::IsAddressValid( image_data_directory ) )
	{
		return 0;
	}

	const auto image_export_directory = reinterpret_cast< const IMAGE_EXPORT_DIRECTORY* >( image + image_data_directory->VirtualAddress );

	if( !memory::IsAddressValid( image_export_directory ) )
	{
		return 0;
	}

	if( !image_export_directory->Base ||
			!image_export_directory->AddressOfFunctions ||
			!image_export_directory->AddressOfNames ||
			!image_export_directory->AddressOfNameOrdinals ||
			!image_export_directory->NumberOfFunctions ||
			!image_export_directory->NumberOfNames )
	{
		return 0;
	}

	const auto functions = reinterpret_cast< const std::uint32_t* >( image + image_export_directory->AddressOfFunctions );
	const auto names = reinterpret_cast< const std::uint32_t* >( image + image_export_directory->AddressOfNames );
	const auto name_ordinals = reinterpret_cast< const std::uint16_t* >( image + image_export_directory->AddressOfNameOrdinals );

	for( auto index = 0ul; index < image_export_directory->NumberOfFunctions; index++ )
	{
		const auto export_ordinal = name_ordinals[ index ];
		const auto export_procedure = functions[ export_ordinal ];

		if( export_procedure )
		{
			const auto export_name = reinterpret_cast< const char* >( image + names[ index ] );

			if( memory::IsAddressValid( export_name ) )
			{
				if( constant::Hash( export_name, true ) == name_hash )
				{
					return ( image + export_procedure );
				}
			}
		}
	}

	return 0;
}
*/

} // namespace horizon::win32