#pragma once
#include <chrono>

//���Ԃ��~���b�P�ʂő���^�C�}�[
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

//���Ԃ����̏ꍇ�Ɏg���^�C�}�[
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
