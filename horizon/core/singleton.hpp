#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "no_copy.hpp"
#include "no_move.hpp"

namespace horizon::core
{

template< class Type >
class Singleton : public NoCopy, public NoMove
{
public:
	static Type& Instance();
};

template< class Type >
Type& Singleton< Type >::Instance()
{
	static Type instance = { };
	return instance;
}

}