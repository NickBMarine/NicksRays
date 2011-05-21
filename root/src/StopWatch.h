#include <Windows.h>
#include <iostream>
using namespace std;
class StopWatch
{
	LARGE_INTEGER _start;
	LARGE_INTEGER _stop;
	LARGE_INTEGER _freq;
	bool _started;
	bool _stopped;
	float _time;
public:
	StopWatch() { QueryPerformanceFrequency(&_freq); _started = false;}
	void Start();
	void Stop();
	float ElapsedTimeS();
	float ElapsedTimeMS();
};