#pragma once
namespace ApUtil {
	int Sign(double n);

	//percentage %の確率でtrueを返す
	bool Chance(int percentage);

	/*
	乱数を最低値と最高値を設定して返す。
	RNG(1,3)なら1, 2, 3のどれかが返る。preciseModeをtrueにするとより精密に乱数を取る。
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
