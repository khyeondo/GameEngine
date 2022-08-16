#ifndef __TIME_H__
#define __TIME_H__

#include <Windows.h>

#include "Singleton.h"

class Time
{
	SINGLETON_H(Time)

private:
	LARGE_INTEGER m_curTime;
	LARGE_INTEGER m_preTime;
	LARGE_INTEGER m_ticksFrequency;

	double m_deltaTime;
	double m_renderFrame;

private:
	Time();

public:
	~Time();
	double GetDeltaTime();
	void SetRenderFrame(double frame);
	double GetRenderFrame();
	void Update();

};

#define DELTA_TIME Time::Instance()->GetDeltaTime()

#endif // _TIME_H_

