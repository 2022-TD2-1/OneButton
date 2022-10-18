#pragma once

float EaseInQuint(float x) {
	return x * x * x * x * x;
}

float EaseOutQuint(float x) {
	if (x > 1)
	{
		int hoge = 0;
	}
	float n = 1 - x;
	return 1 - n * n * n * n * n;
}