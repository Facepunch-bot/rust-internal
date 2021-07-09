#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "../win32/trace.hpp"
#include "../win32/image.hpp"
#include "../win32/process.hpp"

using namespace horizon;

#pragma warning( push )
#pragma warning( disable : 28251 )

void* operator new( std::size_t size )
{
	const auto process_heap = win32::GetProcessHeap();
	return win32::RtlAllocateHeap( process_heap, 0, size );
}

void* operator new[]( std::size_t size )
{
	const auto process_heap = win32::GetProcessHeap();
	return win32::RtlAllocateHeap( process_heap, 0, size );
}

void operator delete( void* data ) noexcept
{
	const auto process_heap = win32::GetProcessHeap();
	win32::RtlFreeHeap( process_heap, 0, data );
}

void operator delete( void* data, std::size_t size ) noexcept
{
	const auto process_heap = win32::GetProcessHeap();
	win32::RtlFreeHeap( process_heap, 0, data );
}

void operator delete[]( void* data ) noexcept
{
	const auto process_heap = win32::GetProcessHeap();
	win32::RtlFreeHeap( process_heap, 0, data );
}

void operator delete[]( void* data, std::size_t size ) noexcept
{
	const auto process_heap = win32::GetProcessHeap();
	win32::RtlFreeHeap( process_heap, 0, data );
}

#pragma warning( pop )