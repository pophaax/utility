#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>

class Timer {

public:
	Timer();
	~Timer() {};

	/*
	 * sets timer start time to current time
	 */
	void start();
	/*
	 * returns seconds passed since timer started
	 */
	double timePassed();
	/*
	 * returns difference between timer running time (from start)
	 * and provided seconds, in seconds
	 */
	double timeUntil(double seconds);
	/*
	 * sleeps until timer reaches provided time 
	 */
	void sleepUntil(double seconds);
	
private:
	std::chrono::steady_clock::time_point m_start;
};

#endif