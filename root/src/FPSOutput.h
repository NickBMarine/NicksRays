#include "StopWatch.h"

class FPSOutput
{
	int _frameCount;
	int _timeElapsedMS;
	float _timeElapsedS;
	int _timeTillUpdate;
	bool _stopWatchTrigger;
	StopWatch _stopWatch;
public:
	FPSOutput(int updateTime);
	void Update();
	void Start();
};

