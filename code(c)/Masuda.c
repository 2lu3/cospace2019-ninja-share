#include "masuda.h"

#define FIND_OBJ_DURATION 45
#define DEPOSIT_OBJ_DURATION 45

#define REP for
#define rep(i, n) REP(int i = 0; i < n; i++)

int world1_first = 0;
int MYROBOTCOLOR = 0;
int depositsisei = 0;
int deposit_nnnuuummm = 0;

int m_log_compass;
int m_log_position[10];

void m_localGameSetup0(void)
{
	// shift-JIS 932
	// UTF-8 65001
	system("chcp 65001");
	//init();
	//init2();
}

void m_Game0(void)
{
	if (getRepeatedNum() != 0)
	{
	}
	//calculate2(US_Left, US_Front, US_Right, Compass + 90);
	//showMap2();
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
	else if (IsOnCyanObj() && loaded_objects[CYAN_LOADED_ID] < 2 && LoadedObjects < 6)
	{
		Find_action(CYAN_LOADED_ID);
	}
	else if (IsOnRedObj() && loaded_objects[RED_LOADED_ID] < 2 && LoadedObjects < 6)
	{
		Find_action(RED_LOADED_ID);
	}
	else if (IsOnBlackObj() && loaded_objects[BLACK_LOADED_ID] < 2 && LoadedObjects < 6)
	{
		Find_action(BLACK_LOADED_ID);
	}
	else if (IsOnDepositArea() && (LoadedObjects >= 5 || Time > 160) && (LoadedObjects > 1))
	{
		printf("2\n");
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
			break;
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
		motor(2, -2);
	}
	/*else if(LoadedObjects >= 4 && !obstacle(8 , 15 , 8)){

		GoToAngle_2(225, 10000);
	}
	else if(obstacle(8 , 15 , 8)){
		//depositのことをかく
	}
	else if(US_Left < 15 && US_Right < 15 && US_Front < 110 && US_Front > 90 && US_Left> 6 && US_Right > 6 && Compass < 290 && Compass > 250 && LoadedObjects >= 5){

		depositsisei++;


	}
	else if (LoadedObjects >= 6 || (LoadedObjects >= 3 && Time > 120))
	{
		if (US_Front < 15)
		{
			motor(-3, 3);
		}
		else if (US_Right < 10)
		{
			motor(2, 4);
		}
		else if (US_Right < 15)
		{
			motor(3, 4);
		}
		else if (US_Right < 40)
		{
			motor(4, 3);
		}
		else if (US_Right < 60)
		{
			motor(4, 1);
		}
		else
		{
			motor(4, 2);
		}
	}*/
	else if (US_Front < 10 || US_Right < 15 || US_Left < 10)
	{

		if (rand() % 5)
		{
			motor(-3, 3);
		}
		else
		{
			motor(3, -3);
		}
		Duration = rand() % 3 + 1;
	}
	else
	{
		/*if (Compass > 245 && Compass < 290) {
			if (US_Front < 15)
			{
				motor(3, -3);
			}
			else if (US_Left < 10)
			{
				motor(4, 1);
			}
			else if (US_Left < 15)
			{
				motor(4, 2);
			}
			else if (US_Left < 15 + rand() % 20)
			{
				if ((Compass > 45 && Compass < 135) || (Compass < 335 && Compass > 225))
				{
					motor(2, 4);
				}
				else
				{
					motor(4, 5);
				}
			}
			else if (US_Left < 50)
			{
				motor(1, 3);
			}
			else
			{
				if (!(rand() % 10))
				{
					motor(4, 5);
				}
				else
				{
					motor(3, 5);
				}
			}
		}else if(LoadedObjects >= 4){
			if (US_Front < 20)
			{
				motor(3, -3);
			}
			else if (US_Left < 20)
			{
				motor(4, 1);
			}
			else if (US_Left < 25)
			{


				motor(4, 2);
			}
			else if (US_Left < 30 + rand() % 20)
			{
				if ((Compass > 45 && Compass < 135) || (Compass < 335 && Compass > 225))
				{
					motor(2, 4);
				}
				else
				{
					motor(4, 5);
				}
			}
			else if (US_Left < 60)
			{
				motor(1, 3);
			}
			else
			{
				if (!(rand() % 10))
				{
					motor(4, 5);
				}
				else
				{
					motor(3, 5);
				}
			}
		}
		else{
			if (US_Front < 15)
			{
				motor(3, -3);
			}
			else if (US_Left < 20)
			{
				motor(4, 1);
			}
			else if (US_Left < 25)
			{


				motor(4, 2);
			}
			else if (US_Left < 30 + rand() % 20)
			{
				if ((Compass > 45 && Compass < 135) || (Compass < 335 && Compass > 225))
				{
					motor(2, 4);
				}
				else
				{
					motor(4, 5);
				}
			}
			else if (US_Left < 60)
			{
				motor(1, 3);
			}
			else
			{
				if (!(rand() % 10))
				{
					motor(4, 5);
				}
				else
				{
					motor(3, 5);
				}
			}
		}*/
		motor(4, 4);
	}

	if (Time > 180 && (getAction() != FIND_OBJ && !IsOnDepositArea()))
	{
		setAction(TELEPORT);
	}
	switch (getAction())
	{
	case DEFINED:
		break;
	case YELLOW_AVOIDANCE:
		if (SuperDuration < 3 && Duration < 3)
		{
			motor_no_action_change(-3, 3);
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
	case TELEPORT:
		Teleport = 2;
		WheelLeft = 0;
		WheelRight = 0;
		LED_1 = 0;
		MyState = 0;
		LoadedObjects = 0;
		SuperDuration = 0;
		for (unsigned int i = 0; i < sizeof(loaded_objects) / sizeof(*loaded_objects); i++)
		{
			loaded_objects[i] = 0;
		}
		CurGame = 1;
		break;
	default:
		break;
	}
}

void m_localGameSetup1(void)
{
	// fp = fopen("motor.txt", "a");
	srand((unsigned int)time(NULL));
	system("cls");

	m_log_compass = Compass;
	m_log_position[0] = PositionX;
	m_log_position[1] = PositionY;
}

void Go_along_the_wall(int range_from_wall, int amplitude)
{

	int a = range_from_wall, b = amplitude; //b =< 10

	if (US_Right < a / 5)
	{
		if (rand() % 100 < b * b)
		{
			motor(-5, -2);
		}
		else
		{
			motor(-4, -2);
		}
	}
	else if (US_Front < a / 2)
	{
		if (rand() % 100 < b * b)
		{
			motor(1, -3);
		}
		else
		{
			motor(1, -2);
		}
	}
	else if (US_Left < a / 5)
	{
		motor(-1, -3);
	}
	else if (US_Left < 15)
	{
		motor(3, 2);
	}
	else if (US_Left < range_from_wall)
	{
		motor(2, 4);
	}
	else if (US_Left < 80)
	{
		motor(1, 3);
	}
	else
	{
		motor(-3, 3);
	}
}

void dotti()
{
	if (world1_first == 0)
	{
		if (US_Left < 50)
		{
			MYROBOTCOLOR = 1;
		}
		else
		{
			MYROBOTCOLOR = 2;
		}
		world1_first++;
	}
}

void Find_action(int color_ID)
{

	setAction(FIND_OBJ);
	loaded_objects[color_ID]++;
	LoadedObjects++;
	SuperDuration = FIND_OBJ_DURATION;
	printf("1\n");
}

void GoToAngle_2(int angle, int distance)
{

	angle = angle - Compass;

	//180より大きい場合
	for (int i = 0; i < 10 && angle > 180; i++)
	{
		angle -= 360;
	}
	//-180より小さい場合
	for (int i = 0; i < 10 && angle < -180; i++)
	{
		angle += 360;
	}
	int classification = obstacle(5, 7, 5);
	// if (LoadedObjects >= 6)
	// {
	//     classification = 0;
	// }

	// double magnification = 0.3;
	int short_front = 1; //(int)(pow(US_Front, magnification) * (5 - (WheelLeft * WheelLeft + WheelRight * WheelRight) / 8) / pow(25, magnification));
	int short_left = 2;  //(int)(pow(US_Left, magnification) * (5 - (WheelLeft * WheelLeft + WheelRight * WheelRight) / 8) / pow(25, magnification));
	int short_right = 2; //(int)(pow(US_Right, magnification) * (5 - (WheelLeft * WheelLeft + WheelRight * WheelRight) / 8) / pow(25, magnification));
	if (short_front < 0)
		short_front = 0;
	if (short_front > 5)
		short_front = 5;
	if (short_right < 0)
		short_right = 0;
	if (short_right > 5)
		short_right = 5;
	if (short_left < 0)
		short_left = 0;
	if (short_left > 5)
		short_left = 5;
	switch (classification)
	{
	case 0:
		classification = obstacle(20, 35, 20);
		if (classification == 1 && angle > 0 && angle < 90)
		{ //left
			motor(5, short_left);
		}
		else if (classification == 2 && abs(angle) < 30)
		{ //front
			if (angle < 0)
			{
				motor(5, short_front);
			}
			else
			{
				motor(short_front, 5);
			}
		}
		else if (classification == 3 && angle > -30 && angle < 90)
		{ //left & front
			motor(5, (short_left < short_front) ? (short_left) : (short_right));
		}
		else if (classification == 4 && angle < 0 && angle > -90)
		{ //right
			motor(short_right, 5);
		}
		else if (classification == 5 && abs(angle) > 30)
		{ //left & right
			if (abs(angle) < 150)
			{
				motor(4, 4);
			}
			else
			{
				if (angle < 0)
				{
					motor(3, -3);
				}
				else
				{
					motor(-3, 3);
				}
				// Duration = 5;
			}
		}
		else if (classification == 6 && angle < 30 && angle > -90)
		{ //front & right
			motor((short_right < short_front) ? (short_right) : (short_right), 5);
		}
		else if (classification == 7)
		{ //all
			if (angle < 0)
			{
				motor(5, short_front);
			}
			else
			{
				motor(short_front, 5);
			}
		}
		else
		{

			// printf("angle = %d\n", angle);
			if (abs(angle) < 20)
			{
				if (distance < 20)
				{
					if (angle < 0)
					{
						motor(3, 2);
					}
					else
					{
						motor(2, 3);
					}
				}
				else
				{

					motor(5, 5);
				}
			}
			else if (abs(angle) < 60)
			{
				if (angle < 0)
				{
					motor(5, 3);
				}
				else
				{
					motor(3, 5);
				}
			}
			else if (abs(angle) < 120)
			{
				if (angle < 0)
				{
					motor(5, 2);
				}
				else
				{
					motor(2, 5);
				}
			}
			else if (distance < 20)
			{
				if (angle < 0)
				{
					motor(0, -3);
				}
				else
				{
					motor(-3, 0);
				}
			}
			else
			{
				if (angle < 0)
				{
					motor(4, -4);
				}
				else
				{
					motor(-4, 4);
				}
				// Duration = 3;
			}
		}
		break;
	case 1: //left
		motor(-2, -3);
		break;
	case 2: //front
		if (US_Left < US_Right)
		{
			motor(-1, -3);
		}
		else
		{
			motor(-3, -1);
		}
		break;
	case 3: //left front
		motor(-2, -3);
		break;
	case 4: //right
		motor(-3, -2);
		break;
	case 5: //left right
		motor(-3, -3);
		break;
	case 6: //front right
		motor(-2, -3);
		break;
	case 7: //left front right
		motor(-3, -3);
		break;
	default:
		break;
	}
	// if(IsOnSwampland()) {
	// 	int max_absolute_value = abs(WheelLeft);
	// 	if(max_absolute_value < abs(WheelRight)) {
	// 		max_absolute_value = abs(WheelRight);
	// 	}
	// 	if(max_absolute_value < 5) {
	// 		if(WheelLeft < 0) {
	// 			WheelLeft -= 5 - max_absolute_value;
	// 		}
	// 		else {
	// 			WheelLeft += 5 - max_absolute_value;
	// 		}
	// 		if(WheelRight < 0) {
	// 			WheelRight -= 5 - max_absolute_value;
	// 		}
	// 		else {
	// 			WheelRight += 5 - max_absolute_value;
	// 		}
	// 	}
	// }
}
