#include "Timer.h"

LimitedTimer::LimitedTimer(double time)
{
	this->time = time;
}

void Timer::Reset()
{
	startTime = currentTime = std::chrono::system_clock::now();
}

double Timer::Check()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
}

void Timer::Start()
{
	startTime = currentTime = std::chrono::system_clock::now();
}

void Timer::Subtract(double time)
{
	startTime = startTime + std::chrono::milliseconds((int)time);
}

void Timer::Update()
{
	currentTime = std::chrono::system_clock::now();
}

void LimitedTimer::Reset()
{
	Timer::Reset();
}

void LimitedTimer::Update()
{
	Timer::Update();
	OnTime();
}

void LimitedTimer::Start()
{
	Timer::Start();
}

void LimitedTimer::SetOnTimeFunction(std::function<void(void)> onTime)
{
	this->onTime = onTime;
}

void LimitedTimer::OnTime()
{
	if ( this->Check() > time )
	{
		int diff = this->Check() - time;
		startTime = currentTime + std::chrono::milliseconds(diff);
		onTime();
	}
}
