#include "timer.hpp"

#include "../core/map_data.hpp"

#include "../win32/time.hpp"
#include "../win32/trace.hpp"

namespace horizon::core
{

Timer::Timer( bool begin /*= false*/ )
	: m_frequency{ }
	, m_begin{ }
	, m_end{ }
{
	g_map_data.RtlQueryPerformanceFrequency( &m_frequency );
	
	if( begin )
	{
		reset();
	}
}

void Timer::reset()
{
	g_map_data.RtlQueryPerformanceCounter( &m_begin );
}

std::int64_t Timer::elapsed()
{
	if( !m_frequency.QuadPart )
	{
		g_map_data.RtlQueryPerformanceFrequency( &m_frequency );
	}

	g_map_data.RtlQueryPerformanceCounter( &m_end );

	const auto count = ( m_end.QuadPart - m_begin.QuadPart );
	return ( count > 0 ? ( ( count * 1000 ) / m_frequency.QuadPart ) : 0 );
}

} // namespace horizon::core