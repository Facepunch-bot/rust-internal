#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "../core/singleton.hpp"

using PIFV = int( * )();
using PVFV = void( * )();

namespace atom::vcruntime
{

class Initializers : public horizon::core::Singleton< Initializers >
{
public:
	~Initializers();

public:
	bool Create();
	void Destroy();

protected:
	int ExecuteConstructorArray( PIFV* begin, PIFV* end );
	void ExecuteConstructorArray( PVFV* begin, PVFV* end );

protected:
	PVFV m_array[ 64 ] = { };
	
	PVFV* m_begin = nullptr;
	PVFV* m_end = nullptr;
};

void init_on_exit_array();

int execute_pifv_array( PIFV* begin, PIFV* end );
void execute_pvfv_array( PVFV* begin, PVFV* end );

int ExecuteInitializers();
void ExecuteTerminators();

} // namespace atom::vcruntime

int crt_init();
void crt_uninit();