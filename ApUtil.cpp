#include "ApUtil.h"
#include <math.h>
#include <stdlib.h>

using namespace ApUtil;

int ApUtil::Sign(double n)
{
	return n < 0 ? -1 : 1;
};

bool ApUtil::Chance(int percentage)
{
	return (ApUtil::RNG(0, 99, true) < percentage);
}

int ApUtil::RNG(int min, int max, bool preciseMode)
{
	if (!preciseMode) {
		return (rand() % (max + 1 - min) + min);
	}

	int ret = 0;
	do {
		ret = rand();
	} while (ret >= RAND_MAX - RAND_MAX % (max + 1 - min));
	ret = ret % (max + 1 - min) + min;
	return ret;
}

double ApUtil::ConvertDegDistToX(double dist, double deg)
{
	return dist * cos(3.1415926 / 180 * deg);
}

double ApUtil::ConvertDegDistToY(double dist, double deg)
{
	return dist * sin(3.1415926 / 180 * deg);
}