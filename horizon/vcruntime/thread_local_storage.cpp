#include "thread_local_storage.hpp"

#include "../memory/operation.hpp"

#include "../win32/image.hpp"
#include "../win32/process.hpp"

extern "C"
{

	std::uint32_t _tls_index = 0;

}; // extern "C"

namespace horizon::vcruntime
{ } // namespace horizon::vcruntime

extern "C"
{

	void __dyn_tls_init( void*, unsigned long reason, void* ) noexcept
	{ }

}; // extern "C"