#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

namespace horizon::core
{

class NoCopy
{
public:
	NoCopy() = default;
	NoCopy( const NoCopy& ) = delete;

protected:
	NoCopy& operator=( const NoCopy& ) = delete;
};

}