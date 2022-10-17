#pragma once
namespace ApUtil {
	int Sign(double n);

	//percentage %�̊m����true��Ԃ�
	bool Chance(int percentage);

	/*
	�������Œ�l�ƍō��l��ݒ肵�ĕԂ��B
	RNG(1,3)�Ȃ�1, 2, 3�̂ǂꂩ���Ԃ�BpreciseMode��true�ɂ���Ƃ�萸���ɗ��������B
	*/
	int RNG(int min, int max, bool preciseMode = false);

	/*Clamp(100,0,5) -> 5, Clip(-5,0,5) -> 0*/
	template<class T> T Clamp(T base, T min, T max)
	{
		return T(base < min ? min : base > max ? max : base);
	}

	double ConvertDegDistToX(double dist, double deg);
	double ConvertDegDistToY(double dist, double deg);
}
