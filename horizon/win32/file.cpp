#include "file.hpp"
#include "basic.hpp"
#include "trace.hpp"

#include "sdk/unicode_string.hpp"
#include "sdk/io_status_block.hpp"

#include "../core/map_data.hpp"

namespace horizon::win32
{

NtFile::NtFile()
	: m_object( nullptr )
{ }

NtFile::~NtFile()
{
	Close();
}

bool NtFile::IsOpen() const
{
	return ( m_object && m_object != INVALID_HANDLE_VALUE );
}

bool NtFile::IsDirectory() const
{
	IO_STATUS_BLOCK io_status_block = { };
	FILE_STANDARD_INFORMATION information = { };

	const auto status = g_map_data.NtQueryInformationFile( m_object, &io_status_block, &information, sizeof( information ), FileStandardInformation );

	if( !NT_SUCCESS( status ) )
	{
		TRACE( "%s: NtQueryInformationFile( ... ) error! (0x%08X)", ATOM_FUNCTION, status );
		return false;
	}

	return ( information.Directory != FALSE );
}

void NtFile::Close()
{
	if( IsOpen() )
	{
		const auto status = g_map_data.NtClose( m_object );

		if( !NT_SUCCESS( status ) )
		{
			TRACE( "%s: NtClose( ... ) error! (0x%08X)", ATOM_FUNCTION, status );
		}
	}

	m_object = nullptr;
}

bool NtFile::OpenInternal( const std::wstring& path, bool create_if_not_existing, std::uint32_t desired_access, std::uint32_t create_options )
{
	constexpr auto share_access = FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE;

	desired_access |= SYNCHRONIZE;
	create_options |= FILE_SYNCHRONOUS_IO_NONALERT;

	const auto create_disposition = ( create_if_not_existing ? FILE_OPEN_IF : FILE_OPEN );

	UNICODE_STRING object_name = { };
	InitializeUnicodeString( &object_name, path.c_str() );

	OBJECT_ATTRIBUTES object_attributes = { };
	InitializeObjectAttributes( &object_attributes, &object_name, OBJ_CASE_INSENSITIVE );

	IO_STATUS_BLOCK io_status_block = { };

	const auto status = g_map_data.NtCreateFile( &m_object, desired_access, &object_attributes, &io_status_block, nullptr, FILE_ATTRIBUTE_NORMAL,
																							 share_access, create_disposition, create_options, nullptr, 0 );

	if( !NT_SUCCESS( status ) )
	{
		TRACE( "%s: NtCreateFile( ... ) error! (0x%08X)", ATOM_FUNCTION, status );
		return false;
	}

	return true;
}

Directory::Directory( const std::wstring& path, bool create_if_not_existing /*= false*/, std::uint32_t desired_access /*= FILE_READ_DATA*/ )
	: NtFile()
{
	if( !Open( path, create_if_not_existing, desired_access ) )
	{
		TRACE( "%s: Open( ... ) error!", ATOM_FUNCTION );
	}
}

bool Directory::Open( const std::wstring& path, bool create_if_not_existing /*= false*/, std::uint32_t desired_access /*= FILE_READ_DATA*/ )
{
	return OpenInternal( path, create_if_not_existing, desired_access, FILE_DIRECTORY_FILE );
}

bool Directory::Query( FILE_DIRECTORY_INFORMATION* information, bool restart /*= false*/ )
{
	IO_STATUS_BLOCK io_status_block = { };

	std::memset( information, 0, sizeof( FILE_DIRECTORY_INFORMATION ) );

	const auto status = g_map_data.NtQueryDirectoryFile( m_object, nullptr, nullptr, nullptr, &io_status_block,
																											 information, sizeof( FILE_DIRECTORY_INFORMATION ),
																											 FileDirectoryInformation, TRUE, nullptr, restart ? TRUE : FALSE );

	if( !NT_SUCCESS( status ) )
	{
		if( status != STATUS_NO_MORE_FILES )
		{
			TRACE( "%s: NtQueryDirectoryFile( ... ) error! (0x%08X)", ATOM_FUNCTION, status );
		}

		return false;
	}

	return true;
}

File::File( const std::wstring& path, bool create_if_not_existing /*= false*/, std::uint32_t desired_access /*= FILE_READ_DATA*/ )
	: NtFile()
{
	if( !Open( path, create_if_not_existing, desired_access ) )
	{
		TRACE( "%s: Open( ... ) error!", ATOM_FUNCTION );
	}
}

bool File::Open( const std::wstring& path, bool create_if_not_existing /*= false*/, std::uint32_t desired_access /*= FILE_READ_DATA*/ )
{
	return OpenInternal( path, create_if_not_existing, desired_access, FILE_NON_DIRECTORY_FILE );
}

bool File::Read( void* data, std::size_t size_to_read, std::size_t* size_read /*= nullptr*/ )
{
	IO_STATUS_BLOCK io_status_block = { };

	const auto status = g_map_data.NtReadFile( m_object, nullptr, nullptr, nullptr, &io_status_block,
																						 data, static_cast< std::uint32_t >( size_to_read ), nullptr, nullptr );

	if( !NT_SUCCESS( status ) )
	{
		TRACE( "%s: NtReadFile( ... ) error! (0x%08X)", ATOM_FUNCTION, status );
		return false;
	}

	if( size_read )
	{
		( *size_read ) = io_status_block.Information;
	}

	return true;
}

bool File::Write( const void* const data, std::size_t size_to_write, std::size_t* size_written /*= nullptr*/ )
{
	IO_STATUS_BLOCK io_status_block = { };

	const auto status = g_map_data.NtWriteFile( m_object, nullptr, nullptr, nullptr, &io_status_block,
																							const_cast< void* >( data ), static_cast< std::uint32_t >( size_to_write ), nullptr, nullptr );

	if( !NT_SUCCESS( status ) )
	{
		TRACE( "%s: NtWriteFile( ... ) error! (0x%08X)", ATOM_FUNCTION, status );
		return false;
	}

	if( size_written )
	{
		( *size_written ) = io_status_block.Information;
	}

	return true;
}

std::size_t File::GetSize() const
{
	IO_STATUS_BLOCK io_status_block = { };
	FILE_STANDARD_INFO information = { };

	const auto status = g_map_data.NtQueryInformationFile( m_object, &io_status_block, &information, sizeof( information ), FileStandardInformation );

	if( !NT_SUCCESS( status ) )
	{
		TRACE( "%s: NtQueryInformationFile( ... ) error! (0x%08X)", ATOM_FUNCTION, status );
		return 0;
	}

	return static_cast< std::size_t >( information.EndOfFile.QuadPart );
}

} // namespace horizon::win32