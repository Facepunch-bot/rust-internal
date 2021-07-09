#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

namespace horizon::vcruntime
{

bool DllMainCRTProcessAttach( void* instance, void* reserved );
bool DllMainCRTProcessDetach( void* reserved );

bool DllMainCRTDispatch( void* instance, std::uint32_t reason, void* reserved );

}

extern "C"
{
	
	BOOL API_WIN32 DllMain( void* instance, unsigned long reason, void* reserved );

	BOOL API_WIN32 _CRT_INIT( void* instance, unsigned long reason, void* reserved );
	BOOL API_WIN32 _DllMainCRTStartup( void* instance, unsigned long reason, void* reserved );

}; // extern "C"