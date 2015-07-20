#include "Timer.h"
#include <thread>

#define STEADY_CLOCK std::chrono::steady_clock
#define DURATION_CAST std::chrono::duration_cast
#define DURATION std::chrono::duration

Timer::Timer() :
	m_start(STEADY_CLOCK::now())
{}

void Timer::start()
{
	m_start = STEADY_CLOCK::now();
}

double Timer::timePassed()
{
	STEADY_CLOCK::time_point end;
	DURATION<double> time_span;

	// the time to count the difference is not included
	end = STEADY_CLOCK::now();
	time_span = DURATION_CAST<DURATION<double>>(end - m_start);
	return time_span.count();
}

double Timer::timeUntil(double seconds)
{
	return seconds - timePassed();
}

void Timer::sleepUntil(double seconds)
{
	long int microseconds;
	int toMicro = 1000*1000;

	microseconds = timeUntil(seconds) * toMicro;
	std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
}