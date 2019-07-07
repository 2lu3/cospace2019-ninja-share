#include "Hikaru.h"

#define FIND_OBJ_DURATION 45
#define DEPOSIT_OBJ_DURATION 45

#define REP for
#define rep(i, n) REP(int i = 0; i < n; i++)

int subject[6] = {0, 0, 0, 0, 0, 0};

int triger_object_num = 5;

int triger(void)
{
	return !((LoadedObjects >= triger_object_num) || (Time > 180 && LoadedObjects >= 3));
}
float log_position[2];

void localGameSetup0(void)
{
	// shift-JIS 932
	// UTF-8 65001
	system("cls");
	system("chcp 65001");
	// init();
	// init2();
}

void localGame0(void)
{
	// calculate2(US_Left, US_Front, US_Right, Compass + 90);
	// if (getRepeatedNum() % 3 == 0)
	// {
	// 	showMap2();
	// }
	if (IsOnTrapBlue())
	{
		for (unsigned int i = 0; i < sizeof(loaded_objects) / sizeof(loaded_objects[0]); i++)
		{
			loaded_objects[i] = 0;
		}
		LoadedObjects = 0;
	}
	if (SuperDuration > 0)
	{
		SuperDuration--;
	}
	else if (IsOnCyanObj() && loaded_objects[CYAN_LOADED_ID] < 3 && LoadedObjects < 6)
	{
		setAction(FIND_OBJ);
		loaded_objects[CYAN_LOADED_ID]++;
		LoadedObjects++;
		SuperDuration = FIND_OBJ_DURATION;
	}
	else if (IsOnRedObj() && loaded_objects[RED_LOADED_ID] < 3 && LoadedObjects < 6)
	{
		setAction(FIND_OBJ);
		loaded_objects[RED_LOADED_ID]++;
		LoadedObjects++;
		SuperDuration = FIND_OBJ_DURATION;
	}
	else if (IsOnBlackObj() && loaded_objects[BLACK_LOADED_ID] < 3 && LoadedObjects < 6)
	{
		setAction(FIND_OBJ);
		loaded_objects[BLACK_LOADED_ID]++;
		LoadedObjects++;
		SuperDuration = FIND_OBJ_DURATION;
	}
	else if (IsOnDepositArea() && LoadedObjects >= 4)
	{
		switch (IsOnDepositArea())
		{
		case 1:
			motor(0, 4);
			break;
		case 2:
			motor(4, 0);
			break;
		case 3:
			motor(0, 0);
			setAction(DEPOSIT_OBJ);
			SuperDuration = DEPOSIT_OBJ_DURATION;
		default:
			break;
		}
	}
	else if (Duration > 0)
	{
		Duration--;
	}
	else if (IsOnYellowLine())
	{
		setAction(YELLOW_AVOIDANCE);
		Duration = 9;
	}
	else if (obstacle(5, 10, 5))
	{
		if (triger())
		{
			motor(2, -2);
		}
		else
		{
			motor(-2, 2);
		}
	}
	else
	{
		motor(3, 3);
	}

	switch (getAction())
	{
	case DEFINED:
		break;
	case YELLOW_AVOIDANCE:
		if (SuperDuration < 3 && Duration < 3)
		{
			if (triger())
			{
				motor_no_action_change(3, -3);
			}
			else
			{
				motor_no_action_change(-3, 3);
			}
		}
		else if ((SuperDuration != 0 && SuperDuration <= 5) || (Duration != 0 && Duration <= 5))
		{
			motor_no_action_change(0, 0);
		}
		else
		{
			motor_no_action_change(-5, -5);
		}
		break;
	case FIND_OBJ:
		motor_no_action_change(0, 0);
		LED_1 = 1;
		break;
	case DEPOSIT_OBJ:
		motor_no_action_change(0, 0);
		LED_1 = 2;
		if (Duration == 0 && SuperDuration == 0)
		{
			for (unsigned int i = 0; i < sizeof(loaded_objects) / sizeof(loaded_objects[0]); i++)
			{
				loaded_objects[i] = 0;
			}
			LoadedObjects = 0;
		}
		else
		{
			if (!IsOnDepositArea())
			{
				Duration = 0;
				SuperDuration = 0;
				LoadedObjects = 6;
				for (int i = 0; i < 3; i++)
				{
					loaded_objects[i] = 2;
				}
			}
		}
		break;
	default:
		break;
	}
}

FILE *fp;

// void localGameSetup1(void)
// {
// 	// fp = fopen("motor.txt", "a");
// 	srand((unsigned int)time(NULL));
// 	system("cls");

// 	log_compass = Compass;
// 	log_position[0] = PositionX;
// 	log_position[1] = PositionY;
// }

/*
void localGame1(void)
{

	// 	int left = 3;
	// 	int right = 5;
	// 	motor(3, 5);
	// 	if (getRepeatedNum() == 0)
	// 	{
	// 		system("cls");
	// 	}
	// 	if (getRepeatedNum() < 20)
	// 	{
	// 		// calculateOdometory(WheelLeft, WheelRight, log_compass, Compass, log_position, position);

	// 		// printf("%lf %lf\n", position[0], position[1]);
	// 		// log_position[0] = position[0];
	// 		// log_position[1] = position[1];
	// 		// log_compass = Compass;
	// 		printf("%d %d %d %d %d\n", WheelLeft, WheelLeft, Compass, PositionX, PositionY);
	// 	}
	// 	// if (getRepeatedNum() == 20)
	// 	// {
	// 	// 	printf("%d %d\n", PositionX, PositionY);
	// 	// }
	// 	// else if (getRepeatedNum() == 40)
	// 	// {
	// 	// 	printf("%d %d\n", PositionX, PositionY);
	// 	// }
	// 	// else if (getRepeatedNum() > 40)
	// 	// {
	// 	// 	motor(0, 0);
	// 	// }
	fflush(stdout);
}*/
