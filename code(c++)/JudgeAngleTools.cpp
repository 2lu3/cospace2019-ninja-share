#include "JudgeAngleTools.hpp"

using namespace std;

//enum Fruit fruit;

int compassJudge(int min, int max)
{
	min %= 360;
	if (min < 0)
		min += 360;
	max %= 360;
	if (max < 0)
		max += 360;

	if (min < max)
	{
		return min <= Compass && Compass <= max;
	}
	else
	{
		return !(max <= Compass && Compass <= min);
	}
}
