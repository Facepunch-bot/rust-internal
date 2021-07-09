#include "storage.hpp"

namespace options
{

CategoryAimbot m_aimbot = { };
CategoryVisuals m_visuals = { };
CategoryCommon m_common = { };
CategoryColors m_colors = { };

struct StorageData
{
	static constexpr auto Signature = HASH( "StorageData" );

	StorageData( bool initialize )
		: m_signature( initialize ? Signature : 0 )
		, m_aimbot()
		, m_visuals()
		, m_common()
		, m_colors()
	{ }

	bool IsValid() const
	{
		return ( m_signature == Signature );
	}

	std::uint64_t m_signature = 0;
	CategoryAimbot m_aimbot = { };
	CategoryVisuals m_visuals = { };
	CategoryCommon m_common = { };
	CategoryColors m_colors = { };
};

bool Load( const std::wstring& name )
{
	std::wstring directory( SECURE( L"\\SystemRoot\\" ) );
	directory.append( name );

	if( directory.find( SECURE( L".bin" ) ) == std::wstring::npos )
	{
		// 
		// Add extension to file path
		// 
		directory.append( SECURE( L".bin" ) );
	}

	win32::File file( directory, true, FILE_READ_DATA );

	if( file.IsOpen() )
	{
		StorageData storage( false );

		if( file.Read( &storage, sizeof( storage ) ) )
		{
			if( storage.IsValid() )
			{
				std::memcpy( &m_aimbot, &storage.m_aimbot, sizeof( CategoryAimbot ) );
				std::memcpy( &m_visuals, &storage.m_visuals, sizeof( CategoryVisuals ) );
				std::memcpy( &m_common, &storage.m_common, sizeof( CategoryCommon ) );
				std::memcpy( &m_colors, &storage.m_colors, sizeof( CategoryColors ) );
				return true;
			}
			else
			{
				TRACE( "%s: Storage data is not valid!", ATOM_FUNCTION );
			}
		}
		else
		{
			TRACE( "%s: Couldn't read file!", ATOM_FUNCTION );
		}
	}
	else
	{
		TRACE( "%s: Couldn't open file!", ATOM_FUNCTION );
	}

	return false;
}

bool Save( const std::wstring& name )
{
	std::wstring directory( SECURE( L"\\SystemRoot\\" ) );
	directory.append( name );

	if( directory.find( SECURE( L".bin" ) ) == std::wstring::npos )
	{
		// 
		// Add extension to file path
		// 
		directory.append( SECURE( L".bin" ) );
	}

	win32::File file( directory, true, FILE_READ_DATA | FILE_WRITE_DATA );

	if( file.IsOpen() )
	{
		StorageData storage( true );
		
		std::memcpy( &storage.m_aimbot, &m_aimbot, sizeof( CategoryAimbot ) );
		std::memcpy( &storage.m_visuals, &m_visuals, sizeof( CategoryVisuals ) );
		std::memcpy( &storage.m_common, &m_common, sizeof( CategoryCommon) );
		std::memcpy( &storage.m_colors, &m_colors, sizeof( CategoryColors ) );

		if( file.Write( &storage, sizeof( storage ) ) )
		{
			return true;
		}
		else
		{
			TRACE( "%s: Couldn't write file!", ATOM_FUNCTION );
		}
	}
	else
	{
		TRACE( "%s: Couldn't open file!", ATOM_FUNCTION );
	}

	return false;
}

} // namespace options