#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "operation.hpp"

namespace horizon::memory
{

class DetourHook
{
public:
	using Shared = std::shared_ptr< DetourHook >;

public:
	DetourHook( std::uint8_t* const destination, const std::uint8_t* const source, std::size_t size = 12 );
	~DetourHook();

public:
	bool Create( std::uint8_t* const destination, const std::uint8_t* const source, std::size_t size = 12 );
	void Destroy();

public:
	template< typename Type, typename... ArgPack >
	inline Type Call( ArgPack... arg_pack )
	{
		using Fn = Type( API_STDCALL* )( ArgPack... );
		const auto procedure = reinterpret_cast< Fn >( m_hooked ? m_jmp_back : m_destination );

		if( !memory::IsAddressValid( procedure ) )
		{
			return std::invoke_result_t< Fn, ArgPack... >();
		}

		return procedure( arg_pack... );
	}

	inline std::uint8_t* GetDestination() const
	{
		return m_destination;
	}
	
	inline const std::uint8_t* GetSource() const
	{
		return m_source;
	}
	
	inline std::size_t GetSize() const
	{
		return m_size;
	}

	inline std::uint8_t* GetJmpBack() const
	{
		return m_jmp_back;
	}

	inline std::uint8_t* GetJmpHook() const
	{
		return m_jmp_hook;
	}

	inline bool IsHooked() const
	{
		return m_hooked;
	}

protected:
	std::uint8_t* m_destination = nullptr;
	const std::uint8_t* m_source = nullptr;
	std::size_t m_size = 0;

	std::uint8_t* m_jmp_back = nullptr;
	std::uint8_t* m_jmp_hook = nullptr;

	bool m_hooked = false;
};

} // namespace horizon::memory