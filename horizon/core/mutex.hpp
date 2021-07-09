#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "../win32/sdk/handle.hpp"

#include "../win32/sdk/rtl_critical_section.hpp"
#include "../win32/sdk/rtl_condition_variable.hpp"

#include "no_copy.hpp"
#include "no_move.hpp"

namespace horizon::core
{

class Mutex : public NoCopy
{
protected:
	friend class ConditionVariable;

public:
	Mutex( std::int32_t spin_count = 0 );

public:
	~Mutex();

public:
	void lock();
	bool try_lock();
	void unlock();

protected:
	win32::RTL_CRITICAL_SECTION m_section = { };
};

class ScopedLock : public NoCopy
{
public:
	explicit ScopedLock( Mutex& mutex );

public:
	~ScopedLock();

protected:
	Mutex& m_mutex;
};

class ConditionVariable : public NoCopy
{
public:
	ConditionVariable();

public:
	~ConditionVariable();

public:
	void notify();
	bool wait_for( Mutex& mutex, std::uint32_t time );

protected:
	win32::RTL_CONDITION_VARIABLE m_cv = { };
	win32::HANDLE m_event = nullptr;
};

} // namespace horizon::core