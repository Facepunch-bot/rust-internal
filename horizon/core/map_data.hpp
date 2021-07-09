#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "../memory/operation.hpp"
#include "../memory/secure_call.hpp"
#include "../memory/system_call.hpp"

#include "../win32/sdk/handle.hpp"
#include "../win32/sdk/access_mask.hpp"
#include "../win32/sdk/io_apc_routine.hpp"
#include "../win32/sdk/io_status_block.hpp"
#include "../win32/sdk/object_attributes.hpp"
#include "../win32/sdk/object_information_class.hpp"
#include "../win32/sdk/object_wait_type.hpp"
#include "../win32/sdk/event_type.hpp"
#include "../win32/sdk/image_runtime_function_entry.hpp"
#include "../win32/sdk/file_information_class.hpp"
#include "../win32/sdk/memory_information_class.hpp"
#include "../win32/sdk/rtl_critical_section.hpp"
#include "../win32/sdk/rtl_condition_variable.hpp"
#include "../win32/sdk/unicode_string.hpp"
#include "../win32/sdk/large_integer.hpp"

#include "../win32/basic.hpp"
#include "../win32/file.hpp"
#include "../win32/image.hpp"
#include "../win32/process.hpp"
#include "../win32/string.hpp"
#include "../win32/time.hpp"
#include "../win32/trace.hpp"

namespace horizon::core
{

#define SECURE_IMPORT( Type, Name, ... )									\
	memory::WrapSecureCall< Type, __VA_ARGS__ > Name = { }

#define SYSTEM_IMPORT( Type, Name, ... )									\
	memory::WrapSystemCall< Type, __VA_ARGS__ > Name = { }

using namespace win32;

struct MapData
{
	bool Create();
	void Destroy();

	bool IsValid() const;
	bool IsValidSubscription();
	bool IsValidConditionVariable() const;

	// 
	// shared data
	// 

	std::uint64_t m_signature = 0;																																										// 0x0000

	std::uintptr_t m_base = 0;																																												// 0x0008
	std::size_t m_size = 0;																																														// 0x0010

	win32::LARGE_INTEGER m_time = { };

	// 
	// native imports
	// 

	SECURE_IMPORT( bool, RtlAddFunctionTable, IMAGE_RUNTIME_FUNCTION_ENTRY*, std::uint32_t, std::uintptr_t );								// 0x0018
	SECURE_IMPORT( bool, RtlDeleteFunctionTable, IMAGE_RUNTIME_FUNCTION_ENTRY* );																						// 0x0020

	SECURE_IMPORT( void*, RtlAllocateHeap, void*, std::uint32_t, std::size_t );																							// 0x0028
	SECURE_IMPORT( void*, RtlReAllocateHeap, void*, std::uint32_t, void*, std::size_t );
	SECURE_IMPORT( bool, RtlFreeHeap, void*, std::uint32_t, void* );																												// 0x0030

	SECURE_IMPORT( bool, RtlQueryPerformanceCounter, LARGE_INTEGER* );																								// 0x0038
	SECURE_IMPORT( bool, RtlQueryPerformanceFrequency, LARGE_INTEGER* );																							// 0x0040

	SECURE_IMPORT( NTSTATUS, RtlInitializeCriticalSection, RTL_CRITICAL_SECTION* );																					// 0x0048
	SECURE_IMPORT( NTSTATUS, RtlInitializeCriticalSectionEx, RTL_CRITICAL_SECTION*, std::int32_t, std::uint32_t );					// 0x0050
	SECURE_IMPORT( NTSTATUS, RtlEnterCriticalSection, RTL_CRITICAL_SECTION* );																							// 0x0058
	SECURE_IMPORT( bool, RtlTryEnterCriticalSection, RTL_CRITICAL_SECTION* );																								// 0x0060
	SECURE_IMPORT( NTSTATUS, RtlLeaveCriticalSection, RTL_CRITICAL_SECTION* );																							// 0x0068
	SECURE_IMPORT( NTSTATUS, RtlDeleteCriticalSection, RTL_CRITICAL_SECTION* );																							// 0x0070

	SECURE_IMPORT( void, RtlInitializeConditionVariable, RTL_CONDITION_VARIABLE* );																					// 0x0078
	SECURE_IMPORT( NTSTATUS, RtlSleepConditionVariableCS, RTL_CONDITION_VARIABLE*, RTL_CRITICAL_SECTION*, LARGE_INTEGER* );	// 0x0080
	SECURE_IMPORT( void, RtlWakeConditionVariable, RTL_CONDITION_VARIABLE* );																								// 0x0088
	SECURE_IMPORT( void, RtlWakeAllConditionVariable, RTL_CONDITION_VARIABLE* );																						// 0x0090

	EXCEPTION_DISPOSITION( API_STDCALL*__C_specific_handler )( EXCEPTION_RECORD*, void*, CONTEXT*, DISPATCHER_CONTEXT* );		// 0x0098

	// 
	// kernel32 imports
	// 

	SECURE_IMPORT( void, OutputDebugStringA, const char* const );																														// 0x00A0
	SECURE_IMPORT( void, OutputDebugStringW, const wchar_t* const );																												// 0x00A8

	// 
	// msvcrt imports
	// 

	SECURE_IMPORT( void*, malloc, std::size_t );																																						// 0x00B0
	SECURE_IMPORT( void, free, void* );																																											// 0x00B8

	SECURE_IMPORT( void*, memchr, void*, int, std::size_t );																																// 0x00C0
	SECURE_IMPORT( int, memcmp, const void*, const void*, std::size_t );																										// 0x00C8
	SECURE_IMPORT( void*, memcpy, void*, const void*, std::size_t );																												// 0x00D0
	SECURE_IMPORT( void*, memmove, void*, void*, std::size_t );																															// 0x00D8
	SECURE_IMPORT( void*, memset, void*, int, std::size_t );																																// 0x00E0

	SECURE_IMPORT( void, qsort, void*, std::size_t, std::size_t, int( * )( const void*, const void* ) );										// 0x00E8
	SECURE_IMPORT( char*, strstr, const char* const, const char* const );																										// 0x00F0

	SECURE_IMPORT( int, _vsnprintf_l, char* const, std::size_t, const char* const, _locale_t, va_list );										// 0x00F8
	SECURE_IMPORT( int, _vsnwprintf_l, wchar_t* const, std::size_t, const wchar_t* const, _locale_t, va_list );							// 0x0100

	SECURE_IMPORT( double, fabs, double );																																									// 0x0108
	SECURE_IMPORT( double, fmod, double, double );																																					// 0x0110
	SECURE_IMPORT( double, pow, double, double );																																						// 0x0118
	SECURE_IMPORT( double, atan2, double, double );																																					// 0x0120
	SECURE_IMPORT( double, ceil, double );																																									// 0x0128
	SECURE_IMPORT( double, floor, double );																																									// 0x0130
	SECURE_IMPORT( long, atol, const char* const );																																					// 0x0138
	SECURE_IMPORT( double, atof, const char* const );																																				// 0x0140

	int( API_CDECL* sscanf )( const char* const, const char* const, ... ) = nullptr;																				// 0x0148

	// 
	// object system api
	// 

	SYSTEM_IMPORT( NTSTATUS, NtClose, HANDLE );																																							// 0x0150
	SYSTEM_IMPORT( NTSTATUS, NtDuplicateObject, HANDLE, HANDLE*, HANDLE, HANDLE*, ACCESS_MASK, bool, std::uint32_t );				// 0x0154
	SYSTEM_IMPORT( NTSTATUS, NtMakeTemporaryObject, HANDLE );																																// 0x0158
	SYSTEM_IMPORT( NTSTATUS, NtQueryObject, HANDLE, OBJECT_INFORMATION_CLASS, void*, std::uint32_t, std::uint32_t* );				// 0x015C
	SYSTEM_IMPORT( NTSTATUS, NtSetInformationObject, HANDLE, OBJECT_INFORMATION_CLASS, void*, std::uint32_t );							// 0x0160
	SYSTEM_IMPORT( NTSTATUS, NtSignalAndWaitForSingleObject, HANDLE, HANDLE, bool, LARGE_INTEGER* );												// 0x0164
	SYSTEM_IMPORT( NTSTATUS, NtWaitForMultipleObjects, std::uint32_t, HANDLE*, OBJECT_WAIT_TYPE, bool, LARGE_INTEGER* );		// 0x0168
	SYSTEM_IMPORT( NTSTATUS, NtWaitForSingleObject, HANDLE, bool, LARGE_INTEGER* );																					// 0x016C

	// 
	// event system api
	// 

	SYSTEM_IMPORT( NTSTATUS, NtClearEvent, HANDLE );																																				// 0x0170
	SYSTEM_IMPORT( NTSTATUS, NtCreateEvent, HANDLE*, ACCESS_MASK, OBJECT_ATTRIBUTES*, EVENT_TYPE, bool );										// 0x0174
	SYSTEM_IMPORT( NTSTATUS, NtOpenEvent, HANDLE*, ACCESS_MASK, OBJECT_ATTRIBUTES* );																				// 0x0178
	SYSTEM_IMPORT( NTSTATUS, NtPulseEvent, HANDLE, std::int32_t* );																													// 0x017C
	SYSTEM_IMPORT( NTSTATUS, NtResetEvent, HANDLE, std::int32_t* );																													// 0x0180
	SYSTEM_IMPORT( NTSTATUS, NtSetEvent, HANDLE, std::int32_t* );																														// 0x0184

	// 
	// file system api
	// 

	SYSTEM_IMPORT( NTSTATUS, NtCreateFile, HANDLE*, ACCESS_MASK, OBJECT_ATTRIBUTES*, IO_STATUS_BLOCK*, LARGE_INTEGER*, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t, void*, std::uint32_t );	// 0x0188
	SYSTEM_IMPORT( NTSTATUS, NtReadFile, HANDLE, HANDLE, IO_APC_ROUTINE*, void*, IO_STATUS_BLOCK*, void*, std::uint32_t, LARGE_INTEGER*, std::uint32_t* );																									// 0x018C
	SYSTEM_IMPORT( NTSTATUS, NtWriteFile, HANDLE, HANDLE, IO_APC_ROUTINE*, void*, IO_STATUS_BLOCK*, void*, std::uint32_t, LARGE_INTEGER*, std::uint32_t* );																									// 0x0190
	SYSTEM_IMPORT( NTSTATUS, NtLockFile, HANDLE, HANDLE, IO_APC_ROUTINE*, void*, IO_STATUS_BLOCK*, LARGE_INTEGER*, LARGE_INTEGER*, std::uint32_t*, bool, bool );																						// 0x0194
	SYSTEM_IMPORT( NTSTATUS, NtUnlockFile, HANDLE, IO_STATUS_BLOCK*, LARGE_INTEGER*, LARGE_INTEGER*, std::uint32_t* );																																											// 0x0198
	SYSTEM_IMPORT( NTSTATUS, NtDeleteFile, OBJECT_ATTRIBUTES* );																																																																						// 0x019C
	SYSTEM_IMPORT( NTSTATUS, NtQueryInformationFile, HANDLE, IO_STATUS_BLOCK*, void*, std::uint32_t, FILE_INFORMATION_CLASS );
	SYSTEM_IMPORT( NTSTATUS, NtQueryDirectoryFile, HANDLE, HANDLE, IO_APC_ROUTINE*, void*, IO_STATUS_BLOCK*, void*, std::uint32_t, FILE_INFORMATION_CLASS, std::uint8_t, UNICODE_STRING*, std::uint8_t );

	// 
	// memory system api
	// 

	SYSTEM_IMPORT( NTSTATUS, NtAllocateVirtualMemory, HANDLE, void**, std::uintptr_t, std::size_t*, std::uint32_t, std::uint32_t );	// 0x01A0
	SYSTEM_IMPORT( NTSTATUS, NtFreeVirtualMemory, HANDLE, void**, std::size_t*, std::uint32_t );																		// 0x01A4
	SYSTEM_IMPORT( NTSTATUS, NtLockVirtualMemory, HANDLE, void**, std::size_t*, std::uint32_t );																		// 0x01A8
	SYSTEM_IMPORT( NTSTATUS, NtUnlockVirtualMemory, HANDLE, void**, std::size_t*, std::uint32_t );																	// 0x01AC
	SYSTEM_IMPORT( NTSTATUS, NtQueryVirtualMemory, HANDLE, void*, MEMORY_INFORMATION_CLASS, void*, std::size_t, std::size_t* );			// 0x01B0
	SYSTEM_IMPORT( NTSTATUS, NtProtectVirtualMemory, HANDLE, void**, std::size_t*, std::uint32_t, std::uint32_t* );									// 0x01B4
	SYSTEM_IMPORT( NTSTATUS, NtReadVirtualMemory, HANDLE, void*, void*, std::size_t, std::size_t* );																// 0x01B8
	SYSTEM_IMPORT( NTSTATUS, NtWriteVirtualMemory, HANDLE, void*, void*, std::size_t, std::size_t* );																// 0x01BC

	// 
	// win32 user api
	// 

	SYSTEM_IMPORT( std::int32_t, NtUserGetKeyNameText, std::int32_t, const wchar_t* const, std::int32_t );													// 0x01C0
	SYSTEM_IMPORT( std::int16_t, NtUserGetKeyState, std::int32_t );																																	// 0x01C4
	SYSTEM_IMPORT( std::int16_t, NtUserGetAsyncKeyState, std::int32_t );																														// 0x01C8
	SYSTEM_IMPORT( std::uint32_t, NtUserMapVirtualKeyEx, std::int32_t, std::uint32_t, std::uintptr_t, std::uint32_t );							// 0x01CC
};

} // namespace horizon::core

extern horizon::core::MapData g_map_data;