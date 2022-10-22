#pragma once
#include <chrono>
#include <functional>

//���Ԃ��~���b�P�ʂő���^�C�}�[
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

//���Ԃ����̏ꍇ�Ɏg���^�C�}�[
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
