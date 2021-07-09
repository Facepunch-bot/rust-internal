#pragma once

#include "../sdk.hpp"

namespace System
{

IL2CPP_NAME_SPACE( "System" );

struct Object : Il2CppObject
{
	IL2CPP_CLASS( "Object" );
};

struct String : Il2CppObject
{
	const wchar_t* c_str() const
	{
		return m_firstChar;
	}

	wchar_t* begin()
	{
		return m_firstChar;
	}

	wchar_t* end()
	{
		return ( begin() + m_stringLength );
	}

	const wchar_t* begin() const
	{
		return m_firstChar;
	}

	const wchar_t* end() const
	{
		return ( begin() + m_stringLength );
	}

	IL2CPP_CLASS( "String" );
	std::int32_t m_stringLength = 0;	// 0x0010
	wchar_t m_firstChar[ 1 ] = { };		// 0x0014
};

template< typename Type >
struct Array : Il2CppArray
{
	Type m_Items[ 1 ] = { };
};

template< typename Type >
struct BufferList : Il2CppObject
{
	std::int32_t count = 0;						// 0x0010
	FIELD_PAD( 0x0004 );							// 0x0014
	Array< Type >* buffer = nullptr;	// 0x0018
};

template< typename KeyType, typename ValueType >
struct ListDictionary : Il2CppObject
{
	FIELD_PAD( 0x0010 );											// 0x0010
	BufferList< KeyType >* keys = nullptr;		// 0x0020
	BufferList< ValueType >* vals = nullptr;	// 0x0040
};

template< typename Type >
struct List : Il2CppObject
{
	Array< Type >* _items = nullptr;		// 0x0010
	std::int32_t _size = 0;							// 0x0018
	std::int32_t _version = 0;					// 0x001C
	Il2CppObject* _syncRoot = nullptr;	// 0x0020
};
// sizeof( List ) = 0x0028

} // namespace System