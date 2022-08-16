#include "../header/EngineTime.h"

SINGLETON_CPP(Time)

Time::Time() :
	m_deltaTime(0.0)
{
	QueryPerformanceFrequency(&m_ticksFrequency);
	QueryPerformanceCounter(&m_curTime);
	QueryPerformanceCounter(&m_preTime);
}

Time::~Time()
{
}

void Time::Update()
{
	QueryPerformanceCounter(&m_curTime);

	m_deltaTime = (m_curTime.QuadPart - m_preTime.QuadPart) / (double)m_ticksFrequency.QuadPart;
	m_preTime = m_curTime;
}

double Time::GetDeltaTime()
{
	return m_deltaTime;
}

void Time::SetRenderFrame(double frame)
{
	m_renderFrame = frame;
}

double Time::GetRenderFrame()
{
	return m_renderFrame;
}
