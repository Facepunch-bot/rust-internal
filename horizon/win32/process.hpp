#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "sdk/handle.hpp"

#include "sdk/teb.hpp"
#include "sdk/peb.hpp"

namespace horizon::win32
{

HANDLE NtCurrentProcess() noexcept;
HANDLE NtCurrentThread() noexcept;
HANDLE NtCurrentSession() noexcept;

TEB* NtCurrentTeb() noexcept;
PEB* NtCurrentPeb() noexcept;

std::uint32_t NtCurrentProcessId() noexcept;
std::uint32_t NtCurrentThreadId() noexcept;

std::int32_t GetLastStatus() noexcept;
void SetLastStatus( std::int32_t last_status ) noexcept;

std::uint32_t GetLastError() noexcept;
void SetLastError( std::uint32_t last_error ) noexcept;

void* GetProcessHeap() noexcept;

void* RtlAllocateHeap( void* heap_handle, std::uint32_t flags, std::size_t size ) noexcept;
void* RtlReAllocateHeap( void* heap_handle, std::uint32_t flags, void* memory_pointer, std::size_t size );
bool RtlFreeHeap( void* heap_handle, std::uint32_t flags, void* memory_pointer ) noexcept;

} // namespace horizon::win32