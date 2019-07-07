#ifndef MASUDA_HPP
#define MASUDA_HPP

#include "CospaceSettings.hpp"
#include "CommonTools.hpp"
#include <random>

// World1
class Game0_Masuda : public UserGame0
{
public:
	void setup(void) override;
	void loop(void) override;
	int shouldTeleport(void) override;
	void taskOnTeleport(void) override;
	const static int kBorderSameObjNum = 2;
	const static int kFindObjDuration = 44;

private:
	ProcessingTime pt;
	int depo = 0;
	int should_deposit =1;
	int deposit_num = 0;
};

// World2
class Game1_Masuda : public UserGame1
{
public:
	void setup(void) override;
	void loop(void) override;

private:
	const static int kCospaceWidth = 360;
	const static int kCospaceHeight = 270;
	const static int kBorderSameObjNum = 2;
	const static int kFindObjDuration = Game0_Masuda::kFindObjDuration;
	int log_superobj_num, log_superobj_x[10], log_superobj_y[10];
	int emergency_x, emergency_y;
	int super_sameoperate = 0;
	int searching_object;
	int log_x = -1, log_y = -1;

	int large_process = -1;
	int process = 0;

	std::random_device rnd;

	void GoToAngle(int angle, int distance);
	int GoToPosition(int x, int y, int wide_decide_x, int wide_decide_y, int wide_judge_arrived);
	long WhereIsMotor(void);
	long WhereIsColorSensor(void);
};

#endif // !MASUDA_HPP
