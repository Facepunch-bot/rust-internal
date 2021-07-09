#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "sdk/access_mask.hpp"

#include "sdk/event_type.hpp"

#include "sdk/file_basic_information.hpp"
#include "sdk/file_id_both_dir_information.hpp"
#include "sdk/file_information_class.hpp"
#include "sdk/file_standard_information.hpp"

#include "sdk/image_base_relocation.hpp"
#include "sdk/image_data_directory.hpp"
#include "sdk/image_dos_header.hpp"
#include "sdk/image_export_directory.hpp"
#include "sdk/image_file_header.hpp"
#include "sdk/image_import_by_name.hpp"
#include "sdk/image_import_descriptor.hpp"
#include "sdk/image_nt_headers.hpp"
#include "sdk/image_optional_header.hpp"
#include "sdk/image_relocation.hpp"
#include "sdk/image_runtime_function_entry.hpp"
#include "sdk/image_section_header.hpp"
#include "sdk/image_thunk_data.hpp"

#include "sdk/io_apc_routine.hpp"
#include "sdk/io_status_block.hpp"

#include "sdk/object_attributes.hpp"
#include "sdk/object_information_class.hpp"
#include "sdk/object_wait_type.hpp"

#include "sdk/memory_information_class.hpp"

#include "sdk/large_integer.hpp"
#include "sdk/ularge_integer.hpp"

#include "sdk/rtl_critical_section.hpp"
#include "sdk/rtl_condition_variable.hpp"

namespace horizon::win32
{

// 
// exception routines
// 
using RtlAddFunctionTableType = bool( API_STDCALL* )( IMAGE_RUNTIME_FUNCTION_ENTRY* FunctionTable, std::uint32_t EntryCount, std::uintptr_t BaseAddress );
using RtlDeleteFunctionTableType = bool( API_STDCALL* )( IMAGE_RUNTIME_FUNCTION_ENTRY* FunctionTable );

// 
// heap routines
// 
using RtlAllocateHeapType = void*( API_STDCALL* )( void* HeapHandle, std::uint32_t Flags, std::size_t Size );
using RtlFreeHeapType = bool( API_STDCALL* )( void* HeapHandle, std::uint32_t Flags, void* BaseAddress );

// 
// performance routines
// 
using RtlQueryPerformanceCounterType = bool( API_STDCALL* )( LARGE_INTEGER* PerformanceCounter );
using RtlQueryPerformanceFrequencyType = bool( API_STDCALL* )( LARGE_INTEGER* PerformanceFrequency );

// 
// critical section routines
// 
using RtlInitializeCriticalSectionType = NTSTATUS( API_STDCALL* )( RTL_CRITICAL_SECTION* CriticalSection );
using RtlInitializeCriticalSectionExType = NTSTATUS( API_STDCALL* )( RTL_CRITICAL_SECTION* CriticalSection, std::uint32_t SpinCount, std::uint32_t Flags );
using RtlEnterCriticalSectionType = NTSTATUS( API_STDCALL* )( RTL_CRITICAL_SECTION* CriticalSection );
using RtlTryEnterCriticalSectionType = bool( API_STDCALL* )( RTL_CRITICAL_SECTION* CriticalSection );
using RtlLeaveCriticalSectionType = NTSTATUS( API_STDCALL* )( RTL_CRITICAL_SECTION* CriticalSection );
using RtlDeleteCriticalSectionType = NTSTATUS( API_STDCALL* )( RTL_CRITICAL_SECTION* CriticalSection );

// 
// condition variable routines
// 
using RtlInitializeConditionVariableType = void( API_STDCALL* )( RTL_CONDITION_VARIABLE* ConditionVariable );
using RtlSleepConditionVariableCSType = NTSTATUS( API_STDCALL* )( RTL_CONDITION_VARIABLE* ConditionVariable, RTL_CRITICAL_SECTION* CriticalSection, LARGE_INTEGER* TimeOut );
using RtlWakeConditionVariableType = void( API_STDCALL* )( RTL_CONDITION_VARIABLE* ConditionVariable );
using RtlWakeAllConditionVariableType = void( API_STDCALL* )( RTL_CONDITION_VARIABLE* ConditionVariable );

// 
// object routines
// 
using NtCloseType = NTSTATUS( API_STDCALL* )( HANDLE ObjectHandle );
using NtDuplicateObjectType = NTSTATUS( API_STDCALL* )( HANDLE SourceProcessHandle, HANDLE* SourceHandle, HANDLE TargetProcessHandle, HANDLE* TargetHandle, ACCESS_MASK DesiredAccess, bool InheritHandle, std::uint32_t Options );
using NtMakeTemporaryObjectType = NTSTATUS( API_STDCALL* )( HANDLE ObjectHandle );
using NtQueryObjectType = NTSTATUS( API_STDCALL* )( HANDLE ObjectHandle, OBJECT_INFORMATION_CLASS ObjectInformationClass, void* ObjectInformation, std::uint32_t ObjectInformationLength, std::uint32_t* ReturnLength );
using NtSetInformationObjectType = NTSTATUS( API_STDCALL* )( HANDLE ObjectHandle, OBJECT_INFORMATION_CLASS ObjectInformationClass, void* ObjectInformation, std::uint32_t ObjectInformationLength );
using NtSignalAndWaitForSingleObjectType = NTSTATUS( API_STDCALL* )( HANDLE ObjectToSignal, HANDLE WaitableObject, bool Alertable, LARGE_INTEGER* TimeOut );
using NtWaitForMultipleObjectsType = NTSTATUS( API_STDCALL* )( std::uint32_t ObjectCount, HANDLE* ObjectsArray, OBJECT_WAIT_TYPE WaitType, bool Alertable, LARGE_INTEGER* TimeOut );
using NtWaitForSingleObjectType = NTSTATUS( API_STDCALL* )( HANDLE ObjectHandle, bool Alertable, LARGE_INTEGER* TimeOut );



} // namespace horizon::win32