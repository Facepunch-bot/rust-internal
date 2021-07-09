#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "../win32/sdk/large_integer.hpp"

#include "no_copy.hpp"

namespace horizon::core
{

class Timer : public NoCopy
{
public:
	Timer( bool begin = false );

public:
	void reset();

	std::int64_t elapsed();

protected:
	win32::LARGE_INTEGER m_frequency = { };
	win32::LARGE_INTEGER m_begin = { };
	win32::LARGE_INTEGER m_end = { };
};

} // namespace horizon::core