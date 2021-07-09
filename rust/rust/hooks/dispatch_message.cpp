#include "dispatch_message.hpp"

#include "../core.hpp"

namespace rust::hooks
{

std::intptr_t API_STDCALL DispatchMessageA( const MSG* msg )
{
	auto& input_manager = win32::InputManager::Instance();

	if( input_manager.OnDispatchMessage( msg ) )
	{
		return 0;
	}

	return memory::Call< std::intptr_t >( m_dispatch_message, msg );
}

} // namespace rust::hooks