#include "FPSOutput.h"

FPSOutput::FPSOutput(int updateTime)
{
	_frameCount = 0;
	_timeElapsedS = 0;
	_stopWatchTrigger = false;
	_timeTillUpdate = updateTime;
	_stopWatch = StopWatch();

}


void FPSOutput::Update()
{
	_frameCount++;
	if (_stopWatchTrigger)
	{
		_stopWatch.Stop();
		_timeElapsedMS = int(_stopWatch.ElapsedTimeMS());
		_timeElapsedS += (_stopWatch.ElapsedTimeS());
		if ( _timeElapsedS >= _timeTillUpdate)
		{
			system("cls");
			printf("Fps: %i \n", int(_frameCount/_timeElapsedS));
			printf("MS: %i \n" , _timeElapsedMS);
			_timeElapsedS = 0;
			_frameCount = 0;
		}
		_stopWatch.Start();
	}
	else
	{
		_stopWatch.Start();
		_stopWatchTrigger = true;
	}
}