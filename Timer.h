#pragma once
#include <chrono>

//時間をミリ秒単位で測るタイマー
class Timer
{
protected:
	using milliseconds = std::chrono::milliseconds;

public:
	void Reset();
	double Check();
	void Start();

	void Update();

protected:
	
	std::chrono::system_clock::time_point currentTime, startTime;
};

//時間が一定の場合に使うタイマー
class LimitedTimer : protected Timer
{
public:
	LimitedTimer(double time);

	void Reset();
	void Start();
	void Update();
	bool IsTime();

private:
	double time;
};
