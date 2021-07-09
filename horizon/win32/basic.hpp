#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "sdk/kuser_shared_data.hpp"

#include "sdk/image_runtime_function_entry.hpp"

#include "sdk/object_attributes.hpp"

#include "sdk/rtl_critical_section.hpp"
#include "sdk/rtl_condition_variable.hpp"

#include "sdk/string.hpp"
#include "sdk/unicode_string.hpp"

#include "sdk/large_integer.hpp"

#if defined( InitializeObjectAttributes )
#undef InitializeObjectAttributes
#endif // InitializeObjectAttributes

namespace horizon::win32
{

KUSER_SHARED_DATA* GetUserSharedData();

void InitializeString( STRING* destination, const char* const source );
void InitializeAnsiString( ANSI_STRING* destination, const char* const source );
void InitializeUnicodeString( UNICODE_STRING* destination, const wchar_t* const source );

void InitializeObjectAttributes( OBJECT_ATTRIBUTES* object_attributes, UNICODE_STRING* object_name = nullptr, std::uint32_t attributes = 0, void* security_descriptor = nullptr, void* security_quality_of_service = nullptr );

bool RtlAddFunctionTable( IMAGE_RUNTIME_FUNCTION_ENTRY* image_runtime_function_entry, std::uint32_t count, std::uintptr_t image );
bool RtlDeleteFunctionTable( IMAGE_RUNTIME_FUNCTION_ENTRY* image_runtime_function_entry );

bool RtlQueryPerformanceCounter( LARGE_INTEGER* counter );
bool RtlQueryPerformanceFrequency( LARGE_INTEGER* frequency );

bool RtlInitializeCriticalSection( RTL_CRITICAL_SECTION* section );
bool RtlInitializeCriticalSectionEx( RTL_CRITICAL_SECTION* section, std::int32_t spin_count, std::uint32_t flags );
bool RtlEnterCriticalSection( RTL_CRITICAL_SECTION* section );
bool RtlTryEnterCriticalSection( RTL_CRITICAL_SECTION* section );
bool RtlLeaveCriticalSection( RTL_CRITICAL_SECTION* section );
bool RtlDeleteCriticalSection( RTL_CRITICAL_SECTION* section );

void RtlInitializeConditionVariable( RTL_CONDITION_VARIABLE* cv );
bool RtlSleepConditionVariableCS( RTL_CONDITION_VARIABLE* cv, RTL_CRITICAL_SECTION* section, LARGE_INTEGER* time );
void RtlWakeConditionVariable( RTL_CONDITION_VARIABLE* cv );
void RtlWakeAllConditionVariable( RTL_CONDITION_VARIABLE* cv );

} // namespace horizon::win32