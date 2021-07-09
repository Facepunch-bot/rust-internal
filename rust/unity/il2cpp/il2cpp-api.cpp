#include "il2cpp-api.hpp"

#include "../sdk.hpp"

void il2cpp_init()
{
	const auto game_assembly = win32::GetImage( HASH( L"GameAssembly.dll" ) );

	if( memory::IsAddressValid( game_assembly ) )
	{
		
	}
}

void il2cpp_shutdown()
{ }