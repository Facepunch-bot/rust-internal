#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

namespace horizon::vcruntime
{

class ThreadLocalStorage
{
public:
	ThreadLocalStorage();

public:
	bool Create();
	void Destroy();

protected:

};

} // namespace horizon::vcruntime