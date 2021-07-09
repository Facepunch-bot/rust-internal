#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

namespace horizon::core
{

class NoMove
{
public:
	NoMove() = default;
	NoMove( NoMove&& ) = delete;

protected:
	NoMove& operator=( NoMove&& ) = delete;
};

}