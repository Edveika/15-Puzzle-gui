#pragma once
#include <chrono>

class Timer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> m_time_start;
	std::chrono::time_point<std::chrono::steady_clock> m_time_end;
	std::chrono::duration<double> m_time_elapsed;

public:
	void start();
	void end();
	double get_time_elapsed() { return m_time_elapsed.count(); }
};