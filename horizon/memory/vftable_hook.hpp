#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "secure_call.hpp"

namespace horizon::memory
{

class VFTableHook
{
public:
	using Unique = std::unique_ptr< VFTableHook >;
	using Shared = std::shared_ptr< VFTableHook >;

public:
	VFTableHook( void* instance );
	~VFTableHook();

public:
	bool Create( void* instance );
	void Destroy();

public:
	void* GetInstance() const;

public:
	void Hook( void* procedure, std::size_t index );
	void Unhook( std::size_t index );

public:
	template< std::size_t N, typename T = std::uintptr_t >
	T Get()
	{
		return T( m_restore[ N ] );
	}

	template< std::size_t N, typename T, typename... ArgPack >
	T Call( void* instance, ArgPack... arg_pack )
	{
		using Fn = T( __thiscall* )( void*, ArgPack... );

		const auto procedure = Get< N, Fn >();
		return procedure( instance, arg_pack... );
	}

	template< std::size_t Index, typename Type, typename... ArgPack >
	inline Type SecureCall( void* instance, ArgPack... arg_pack )
	{
		const auto procedure = Get< Index >();
		return memory::SecureCall< Type, void*, ArgPack... >( procedure, instance, arg_pack... );
	}

protected:
	std::uintptr_t** m_instance = nullptr;
	std::uintptr_t* m_restore = nullptr;
	std::uintptr_t* m_replace = nullptr;
	std::size_t m_size = 0;
};

}