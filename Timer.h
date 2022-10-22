#pragma once
#include <chrono>
#include <functional>

//時間をミリ秒単位で測るタイマー
class Timer
{
protected:
	using milliseconds = std::chrono::milliseconds;

public:
	void Reset();
	double Check();
	void Start();
	void Subtract(double time);

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
	void Update();
	void Start();
	void SetOnTimeFunction(std::function<void(void)> onTime);
	void OnTime();

private:
	double time;
	std::function<void(void)> onTime;
};
