#include "StopWatch.h"


void StopWatch::Start()
{
	if (!_started)
	{
		_started = true;
		QueryPerformanceCounter(&_start);
	}
	else
		printf("Stopwatch has already started\n");
}

void StopWatch::Stop()
{
	if (_started)
	{
		_started = false;
		QueryPerformanceCounter(&_stop);
		_time = float(_stop.QuadPart - _start.QuadPart) / (_freq.QuadPart);
	}
	else
		printf("You need to start the clock\n");
}

float StopWatch::ElapsedTimeS()
{
	return _time;
}

float StopWatch::ElapsedTimeMS()
{
	return _time * 1000;
}
