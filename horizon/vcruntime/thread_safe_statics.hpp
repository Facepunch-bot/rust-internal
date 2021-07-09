#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "../core/mutex.hpp"

namespace horizon::vcruntime
{

// 
// [ class ]
// 
class ThreadSafeStatics;

// 
// [ class ] implementation
// 
class ThreadSafeStatics
{
public:
	ThreadSafeStatics() noexcept;

public:
	bool Initialize() noexcept;
	void Uninitialize() noexcept;

public:
	void OnThreadHeader( std::int32_t& parameter ) noexcept;
	void OnThreadAbort( std::int32_t& parameter ) noexcept;
	void OnThreadFooter( std::int32_t& parameter ) noexcept;

protected:
	void Update() noexcept;
	void UpdateThread() noexcept;

protected:
	void SetEpoch( std::int32_t epoch ) noexcept;
	void SetEpochThread( std::int32_t epoch_thread ) noexcept;

	std::int32_t GetEpoch() const noexcept;
	std::int32_t GetEpochThread() const noexcept;

protected:
	std::int32_t* m_epoch = nullptr;
	std::int32_t* m_epoch_thread = nullptr;

	core::Mutex m_mutex = { 4000 };
	core::ConditionVariable m_condition_variable = { };
};

}

extern horizon::vcruntime::ThreadSafeStatics* g_thread_safe_statics;