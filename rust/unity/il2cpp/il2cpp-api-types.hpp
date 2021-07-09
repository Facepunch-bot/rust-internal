#pragma once

#include <horizon/include/auto.hpp>
#include <horizon/include/base.hpp>
#include <horizon/include/win32.hpp>

#include <horizon/memory/operation.hpp>

struct MethodInfo;

enum class Il2CppProfileFlags
{
	IL2CPP_PROFILE_NONE = 0,
	IL2CPP_PROFILE_APPDOMAIN_EVENTS = 1 << 0,
	IL2CPP_PROFILE_ASSEMBLY_EVENTS = 1 << 1,
	IL2CPP_PROFILE_MODULE_EVENTS = 1 << 2,
	IL2CPP_PROFILE_CLASS_EVENTS = 1 << 3,
	IL2CPP_PROFILE_JIT_COMPILATION = 1 << 4,
	IL2CPP_PROFILE_INLINING = 1 << 5,
	IL2CPP_PROFILE_EXCEPTIONS = 1 << 6,
	IL2CPP_PROFILE_ALLOCATIONS = 1 << 7,
	IL2CPP_PROFILE_GC = 1 << 8,
	IL2CPP_PROFILE_THREADS = 1 << 9,
	IL2CPP_PROFILE_REMOTING = 1 << 10,
	IL2CPP_PROFILE_TRANSITIONS = 1 << 11,
	IL2CPP_PROFILE_ENTER_LEAVE = 1 << 12,
	IL2CPP_PROFILE_COVERAGE = 1 << 13,
	IL2CPP_PROFILE_INS_COVERAGE = 1 << 14,
	IL2CPP_PROFILE_STATISTICAL = 1 << 15,
	IL2CPP_PROFILE_METHOD_EVENTS = 1 << 16,
	IL2CPP_PROFILE_MONITOR_EVENTS = 1 << 17,
	IL2CPP_PROFILE_IOMAP_EVENTS = 1 << 18,
	IL2CPP_PROFILE_GC_MOVES = 1 << 19,
	IL2CPP_PROFILE_FILEIO = 1 << 20,
};
// sizeof( Il2CppProfileFlags ) = 0x0004

enum class Il2CppProfileFileIOKind
{
	IL2CPP_PROFILE_FILEIO_WRITE = 0,
	IL2CPP_PROFILE_FILEIO_READ,
};
// sizeof( Il2CppProfileFileIOKind ) = 0x0004

enum class Il2CppGCEvent
{
	IL2CPP_GC_EVENT_START,
	IL2CPP_GC_EVENT_MARK_START,
	IL2CPP_GC_EVENT_MARK_END,
	IL2CPP_GC_EVENT_RECLAIM_START,
	IL2CPP_GC_EVENT_RECLAIM_END,
	IL2CPP_GC_EVENT_END,
	IL2CPP_GC_EVENT_PRE_STOP_WORLD,
	IL2CPP_GC_EVENT_POST_STOP_WORLD,
	IL2CPP_GC_EVENT_PRE_START_WORLD,
	IL2CPP_GC_EVENT_POST_START_WORLD,
};
// sizeof( Il2CppGCEvent ) = 0x0004

enum class Il2CppStat
{
	IL2CPP_STAT_NEW_OBJECT_COUNT,
	IL2CPP_STAT_INITIALIZED_CLASS_COUNT,
	IL2CPP_STAT_METHOD_COUNT,
	IL2CPP_STAT_CLASS_STATIC_DATA_SIZE,
	IL2CPP_STAT_GENERIC_INSTANCE_COUNT,
	IL2CPP_STAT_GENERIC_CLASS_COUNT,
	IL2CPP_STAT_INFLATED_METHOD_COUNT,
	IL2CPP_STAT_INFLATED_TYPE_COUNT,
};
// sizeof( Il2CppStat ) = 0x0004

enum class Il2CppRuntimeUnhandledExceptionPolicy
{
	IL2CPP_UNHANDLED_POLICY_LEGACY,
	IL2CPP_UNHANDLED_POLICY_CURRENT,
};
// sizeof( Il2CppRuntimeUnhandledExceptionPolicy ) = 0x0004

struct Il2CppStackFrameInfo
{
	const MethodInfo* method = nullptr;	// 0x0000
};
// sizeof( Il2CppStackFrameInfo ) = 0x0008

struct Il2CppMemoryCallbacks
{
	void*( *malloc_func )( std::size_t size ) = nullptr;																						// 0x0000
	void*( *aligned_malloc_func )( std::size_t size, std::size_t alignment ) = nullptr;							// 0x0008
	void( *free_func )( void* ptr ) = nullptr;																											// 0x0010
	void( *aligned_free_func )( void* ptr ) = nullptr;																							// 0x0018
	void*( *calloc_func )( std::size_t nmemb, std::size_t size ) = nullptr;													// 0x0020
	void*( *realloc_func )( void* ptr, std::size_t size ) = nullptr;																// 0x0028
	void*( *aligned_realloc_func )( void* ptr, std::size_t size, std::size_t alignment ) = nullptr;	// 0x0030
};
// sizeof( Il2CppMemoryCallbacks ) = 0x0038

using Il2CppChar = wchar_t;
// sizeof( Il2CppChar ) = 0x0002

using Il2CppNativeChar = wchar_t;
// sizeof( Il2CppNativeChar ) = 0x0002

#define IL2CPP_NATIVE_STRING( str )		L ## str

using Il2CppMethodPointer = void( * )();
// sizeof( Il2CppMethodPointer ) = 0x0008

#define ARRAY_LENGTH_AS_INT32( a )		( ( std::int32_t )a )