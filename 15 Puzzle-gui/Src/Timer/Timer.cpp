#include "Timer.h"

void Timer::start()
{
	m_time_start = std::chrono::steady_clock::now();
}

void Timer::end()
{
	m_time_end = std::chrono::steady_clock::now();
	m_time_elapsed += (m_time_end - m_time_start) / 1000'000'0; // this is so we dont see too many unnecessary numbers...
}