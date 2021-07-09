#pragma once

#include <horizon/include/auto.hpp>
#include <horizon/include/base.hpp>
#include <horizon/include/win32.hpp>

#include <horizon/memory/operation.hpp>

#include "il2cpp-blob.hpp"
#include "il2cpp-metadata.hpp"

struct Il2CppClass;
struct Il2CppType;

struct MethodInfo;

struct Il2CppArrayType
{
	const Il2CppType* etype = nullptr;	// 0x0000
	std::uint8_t rank = 0;							// 0x0008
	std::uint8_t numsizes = 0;					// 0x0009
	std::uint8_t numlobounds = 0;				// 0x000A
	FIELD_PAD( 0x0005 );								// 0x000B
	std::int32_t* sizes = nullptr;			// 0x0010
	std::int32_t* lobounds = nullptr;		// 0x0018
};
// sizeof( Il2CppArrayType ) = 0x0020

struct Il2CppGenericInst
{
	std::uint32_t type_argc = 0;						// 0x0000
	FIELD_PAD( 0x0004 );										// 0x0004
	const Il2CppType** type_argv = nullptr;	// 0x0008
};
// sizeof( Il2CppGenericInst ) = 0x0010

struct Il2CppGenericContext
{
	const Il2CppGenericInst* class_inst = nullptr;	// 0x0000
	const Il2CppGenericInst* method_inst = nullptr;	// 0x0008
};
// sizeof( Il2CppGenericContext ) = 0x0010

struct Il2CppGenericParameter
{
	std::int32_t ownerIndex = -1;				// 0x0000
	std::int32_t nameIndex = -1;				// 0x0004
	std::int32_t constraintsStart = -1;	// 0x0008
	std::int16_t constraintsCount = 0;	// 0x000C
	std::uint16_t num = 0;							// 0x000E
	std::uint16_t flags = 0;						// 0x0010
	FIELD_PAD( 0x0002 );								// 0x0012
};
// sizeof( Il2CppGenericParameter ) = 0x0014

struct Il2CppGenericContainer
{
	std::int32_t ownerIndex = -1;							// 0x0000
	std::int32_t type_argc = 0;								// 0x0004
	std::int32_t is_method = 0;								// 0x0008
	std::int32_t genericParameterStart = -1;	// 0x000C
};
// sizeof( Il2CppGenericContainer ) = 0x0010

struct Il2CppGenericClass
{
	std::int32_t typeDefinitionIndex = -1;	// 0x0000
	FIELD_PAD( 0x0004 );										// 0x0004
	Il2CppGenericContext context = { };			// 0x0008
	Il2CppClass* cached_class = nullptr;		// 0x0018
};
// sizeof( Il2CppGenericClass ) = 0x0020

struct Il2CppGenericMethod
{
	const MethodInfo* methodDefinition = nullptr;	// 0x0000
	Il2CppGenericContext context = { };						// 0x0008
};
// sizeof( Il2CppGenericMethod ) = 0x0018

struct Il2CppType
{
	union
	{
		void* dummy = nullptr;							// 0x0000
		std::int32_t klassIndex;						// 0x0000
		const Il2CppType* type;							// 0x0000
		Il2CppArrayType* array;							// 0x0000
		std::int32_t genericParameterIndex;	// 0x0000
		Il2CppGenericClass* generic_class;	// 0x0000
	} data = { };													// 0x0000
	std::uint32_t attrs : 16;							// 0x0008
	Il2CppTypeEnum type : 8;							// 0x0008
	std::uint32_t num_mods : 6;						// 0x0008
	std::uint32_t byref : 1;							// 0x0008
	std::uint32_t pinned : 1;							// 0x0008
	FIELD_PAD( 0x0004 );									// 0x000C
};
// sizeof( Il2CppType ) = 0x0010

enum class Il2CppCallConvention
{
	IL2CPP_CALL_DEFAULT,
	IL2CPP_CALL_C,
	IL2CPP_CALL_STDCALL,
	IL2CPP_CALL_THISCALL,
	IL2CPP_CALL_FASTCALL,
	IL2CPP_CALL_VARARG,
};
// sizeof( Il2CppCallConvention ) = 0x0004

enum class Il2CppCharSet
{
	CHARSET_ANSI,
	CHARSET_UNICODE,
	CHARSET_NOT_SPECIFIED,
};
// sizeof( Il2CppCharSet ) = 0x0004