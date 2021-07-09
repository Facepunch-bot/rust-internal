#include "detour_hook.hpp"

#include "../core/map_data.hpp"

#include "../win32/trace.hpp"
#include "../win32/image.hpp"
#include "../win32/process.hpp"

namespace horizon::memory
{

constexpr std::uint8_t jmp_code_x64[] =
{
	0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// mov rax, imm64
	0xFF, 0xE0,																									// jmp rax
};

DetourHook::DetourHook( std::uint8_t* const destination, const std::uint8_t* const source, std::size_t size /*= 12*/ )
{
	if( !Create( destination, source, size ) )
	{
		TRACE( "%s: Create( 0x%016llX, 0x%016llX, 0x%016llX ) error!", FN, memory::ToAddress( destination ), memory::ToAddress( source ), size );
	}
}

DetourHook::~DetourHook()
{
	Destroy();
}

bool DetourHook::Create( std::uint8_t* const destination, const std::uint8_t* const source, std::size_t size /*= 12*/ )
{
	m_destination = destination;

	if( !memory::IsAddressValid( m_destination ) )
	{
		TRACE( "%s: m_destination is not valid!", FN );
		return false;
	}

	m_source = source;

	if( !memory::IsAddressValid( m_source ) )
	{
		TRACE( "%s: m_source is not valid!", FN );
		return false;
	}

	m_size = size;

	if( m_size < sizeof( jmp_code_x64 ) )
	{
		TRACE( "%s: m_size is not valid! (%llu)", FN, m_size );
		return false;
	}

	const auto process = win32::NtCurrentProcess();

	void* jmp_back_base = nullptr;
	auto jmp_back_size = m_size + sizeof( jmp_code_x64 );
	
	auto status = g_map_data.NtAllocateVirtualMemory( process, &jmp_back_base, 0, &jmp_back_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );

	if( NT_SUCCESS( status ) )
	{
		m_jmp_back = static_cast< std::uint8_t* >( jmp_back_base );

		auto destination_base = static_cast< void* >( m_destination );
		auto destination_size = m_size;
		
		auto destination_protection = static_cast< std::uint32_t >( PAGE_NOACCESS );

		// 
		// make memory writeable
		// 
		status = g_map_data.NtProtectVirtualMemory( process, &destination_base, &destination_size, PAGE_EXECUTE_READWRITE, &destination_protection );

		if( NT_SUCCESS( status ) )
		{
			// save bytes
			std::memcpy( m_jmp_back, m_destination, m_size );

			// append jmp back code
			std::memcpy( m_jmp_back + m_size + 0, jmp_code_x64, sizeof( jmp_code_x64 ) );

			// set jmp back (rax) address
			std::memcpy( m_jmp_back + m_size + 2, &destination_base, sizeof( destination_base ) );

			void* jmp_hook_base = nullptr;
			auto jmp_hook_size = m_size;

			status = g_map_data.NtAllocateVirtualMemory( process, &jmp_hook_base, 0, &jmp_hook_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );

			if( NT_SUCCESS( status ) )
			{
				m_jmp_hook = static_cast< std::uint8_t* >( jmp_hook_base );

				// make jmp hook code
				std::memcpy( m_jmp_hook + 0, jmp_code_x64, sizeof( jmp_code_x64 ) );

				// set jmp hook (rax) address
				std::memcpy( m_jmp_hook + 2, &m_source, sizeof( m_source ) );

				// is resize required
				if( m_size > sizeof( jmp_code_x64 ) )
				{
					// change spare bytes to 'nop'
					std::memset( m_jmp_hook + sizeof( jmp_code_x64 ), 0x90, m_size - sizeof( jmp_code_x64 ) );
				}

				// change destination bytes to jmp hook code
				std::memcpy( m_destination, m_jmp_hook, sizeof( jmp_code_x64 ) );

				// set internal state
				m_hooked = true;
				return true;
			}
			else
			{
				TRACE( "%s: win32::AllocateVirtualMemory( ... ) error!", FN );
			}
		}
		else
		{
			TRACE( "%s: win32::ProtectVirtualMemory( ... ) error!", FN );
		}
	}
	else
	{
		TRACE( "%s: win32::AllocateVirtualMemory( ... ) error!", FN );
	}

	return false;
}

void DetourHook::Destroy()
{
	if( m_hooked )
	{

	}
}

} // namespace horizon::memory