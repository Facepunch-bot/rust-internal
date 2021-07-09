#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

namespace horizon::vcruntime
{ } // namespace horizon::vcruntime

const void* memchr( const void* data, int value, std::size_t size );
int memcmp( const void* source, const void* destination, std::size_t size );
void* memcpy( void* destination, const void* source, std::size_t size );
void* memmove( void* destination, const void* source, std::size_t size );
void* memset( void* destination, int value, std::size_t size );