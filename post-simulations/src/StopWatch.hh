// -----------------------------------
// Author: Allan Jales
//
// Description: This class functions as a stopwatch to measure the elapsed time between two points in the code. 
// It provides functionality to start, stop, and retrieve the elapsed time in a human-readable format with appropriate units.
// -----------------------------------

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <iostream>
using namespace std;
#include <chrono>
using namespace chrono;

class StopWatch
{
private:
    using clock = std::chrono::steady_clock;
    using time_point = clock::time_point;
    using duration = clock::duration;

	time_point begin;
	time_point end;

	/// @brief Indicates whether the timer has been stopped.
	bool hasStoppedTimer = false;
public:
	StopWatch();
	~StopWatch();

	/// @brief Starts or restarts the timer.
	void Start();

	/// @brief Stops the timer.
	void Stop();

	string TimeElapsedString();
};

StopWatch::StopWatch()
{
	Start();
	end = clock::now();
}

StopWatch::~StopWatch()
{}

void StopWatch::Start()
{
	begin = clock::now();
	hasStoppedTimer = false;
}

void StopWatch::Stop()
{
	hasStoppedTimer = true;
	end = clock::now();
}

/// @brief Retrieves the current elapsed time as a string, automatically selecting the most appropriate units.
/// @return A string representing the elapsed time.
string StopWatch::TimeElapsedString()
{
	// If wasn't stopped, then elapsed time is from begin to now
	if (!hasStoppedTimer)
		end = clock::now();
	
	duration elapsed = end - begin;
	string unit = " ticks";

	if (duration_cast<nanoseconds>(elapsed).count() < 1e3)
		return to_string(duration_cast<nanoseconds>(elapsed).count()) + " nanoseconds";
	if (duration_cast<microseconds>(elapsed).count() < 1e3)
		return to_string(duration_cast<microseconds>(elapsed).count()) + " microseconds";
	if (duration_cast<milliseconds>(elapsed).count() < 1e3)
		return to_string(duration_cast<milliseconds>(elapsed).count()) + " milliseconds";
	if (duration_cast<seconds>(elapsed).count() < 60)
		return to_string(duration_cast<seconds>(elapsed).count()) + " seconds";
	
	return to_string(chrono::duration_cast<chrono::minutes>(end - begin).count()) + " minutes";
}

#endif