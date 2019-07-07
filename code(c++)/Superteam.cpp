
#include "Superteam.hpp"
#include <iostream>

#define IF if
#define LOG_MESSAGE(MESSAGE, OPTION) \
	IF((OPTION) <= getRunMode()) { logErrorMessage.logMessage((MESSAGE), (OPTION)); }
#define ERROR_MESSAGE(MESSAGE, OPTION) \
	IF((OPTION) <= getRunMode()) { logErrorMessage.errorMessage((MESSAGE), (OPTION)); }

#define FUNC_NAME getFuncName(__FUNCTION__)

using namespace std;

void Game0_Superteam::setup(void)
{
	pt.start();

	setRunMode(MODE_DEBUG);
	UserGame0::setup();

	logErrorMessage.delErrorFile();
	logErrorMessage.delLogFile();
	InputColorInformation();

	double seconds = pt.end();
	LOG_MESSAGE(FUNC_NAME + "(): " + to_string(seconds) + " milliseconds", MODE_NORMAL);
	// if (compassJudge(265,275))
	// {

	// }

}

void Game0_Superteam::loop(void)
{
	int reserved_space = LoadedObjects;
	if (loaded_objects[CYAN_LOADED_ID] == 0) {
		reserved_space++;
	}
	if (loaded_objects[RED_LOADED_ID] == 0) {
		reserved_space++;
	}
	if (loaded_objects[BLACK_LOADED_ID] == 0) {
		reserved_space++;
	}
	UserGame0::loop();
	pt.start();
	LOG_MESSAGE("World1 loop start", MODE_NORMAL);
	//cout<<depo<<endl;
	//cout << IsOnDepositArea() << endl;
	/*if (robot_color)
	{
		
	} */
	
	if (SuperDuration > 0)
	{
		SuperDuration--;
	}
	else if (IsOnDepositArea() 
    &&( (loaded_objects[RED_LOADED_ID]>0 && loaded_objects[CYAN_LOADED_ID]>0 && loaded_objects[BLACK_LOADED_ID]>0)||(Time>150 &&Time<175)))
	{
		depo = 0;
		LOG_MESSAGE("find object box", MODE_DEBUG);
		switch (IsOnDepositArea())
		{
		case 1:
			LOG_MESSAGE("Left Sensor is in object_box", MODE_DEBUG);
			motor(0, 5);
			break;
		case 2:
			LOG_MESSAGE("Right Sensor is in object_box", MODE_DEBUG);
			motor(5, 0);
			break;
		case 3:
			LOG_MESSAGE("I am in object_box", MODE_DEBUG);
			setAction(DEPOSIT_OBJ);
			SuperDuration = 60;

			deposit_num++;
			Duration = 0;
			break;
		default:
			break;
		}
	}
	else if (EitherColorJudge(black_obj) && LoadedObjects < 6 && loaded_objects[BLACK_LOADED_ID] < 4
		&& (loaded_objects[BLACK_LOADED_ID] == 0 
			|| 6 - reserved_space > 0))
	{
		LOG_MESSAGE("find black obj", MODE_NORMAL);
		setAction(FIND_OBJ);
		loaded_objects[BLACK_LOADED_ID]++;
		SuperDuration = kFindObjDuration;
	}
	else if (EitherColorJudge(cyan_obj) && LoadedObjects < 6 && loaded_objects[CYAN_LOADED_ID] < 4
		&& (loaded_objects[CYAN_LOADED_ID] == 0 || 6 - reserved_space > 0))
	{
		LOG_MESSAGE("find cyan obj", MODE_NORMAL);
		setAction(FIND_OBJ);
		loaded_objects[CYAN_LOADED_ID]++;
		SuperDuration = kFindObjDuration;
	}
	else if (EitherColorJudge(red_obj) && LoadedObjects < 6 && loaded_objects[RED_LOADED_ID] < 4
		&& (loaded_objects[RED_LOADED_ID] == 0 || 6- reserved_space > 0))
	{
		LOG_MESSAGE("find red obj", MODE_NORMAL);
		setAction(FIND_OBJ);
		loaded_objects[RED_LOADED_ID]++;
		SuperDuration = kFindObjDuration;
	}
	else if (Duration > 0)
	{
		Duration--;
	}
	else if (Time < 1)
	{
		motor(5, 1);
		Duration = 2;
	}

	else if (IsOnYellowLine())
	{
		/*if (IsOnYellowLine() == 1)
		{
			motor(-1, -3);
		}
		else
		{*/
			//motor(-3, -1);
		//}
		setAction(YELLOW_AVOIDANCE);
		Duration = 10;
	}else if(compassJudge(165,195))
	{
        if (US_Left<15 && US_Right<15 && compassJudge(65,100)&&US_Front>100)
        {
            motor(-4,-2);
        }
        else if (US_Left<15 && US_Right<15 && compassJudge(260,295)&&US_Front>100)
        {
            motor(-2,-4);
        }
		else if (US_Front < 10)
		{
			motor(-4, 4);
		}
		else if (US_Right < 5)
		{
			motor(-3, -1);
		}
		else if (US_Right < 10)
		{
			motor(3, 4);
		}
		else if (US_Right < 20)
		{
			motor(4, 3);
		}
		else if (US_Right < 50)
		{
			motor(4, 2);
		}
		else
		{
			motor(4, 3);
		}
	}
	else
	{
        if (US_Left<15 && US_Right<15 && compassJudge(65,100)&&US_Front>100)
        {
            motor(-4,-2);
        }
        else if (US_Left<15 && US_Right<15 && compassJudge(260,295)&&US_Front>100)
        {
            motor(-2,-4);
        }
		else if (US_Front < 10)
		{
			motor(-4, 4);
		}
		else if (US_Right < 5)
		{
			motor(-3, -1);
		}
		else if (US_Right < 10)
		{
			motor(3, 4);
		}
		else if (US_Right < 20)
		{
			motor(4, 3);
		}
		else if (US_Right < 50)
		{
			motor(4, 2);
		}
		else
		{
			motor(5, 1);
		}
	}
	
	

	/*if (Time > 180 && getAction() != FIND_OBJ && getAction() != DEPOSIT_OBJ && (!EitherColorJudge(object_box) && LoadedObjects < 3) || Time > 200)
	{
		LOG_MESSAGE("Teleport");
		setAction(TELEPORT);
	}*/

	switch (getAction())
	{
	case DEFINED:
		break;
	case YELLOW_AVOIDANCE:
		if (LoadedObjects > 0){
			if (Duration < 4) {
				motor_no_action_change(2, -3);
			}
			else {
				motor_no_action_change(-3, -3);
			}
		}else
		{
			motor(5,4);
		}
		
		
		break;
	case FIND_OBJ:
		if (Duration == kFindObjDuration || SuperDuration == kFindObjDuration)
		{
			LOG_MESSAGE("Add 1 to LoadedObjects", MODE_VERBOSE);
			LoadedObjects++;
		}
		LED_1 = 1;
		MyState = 0;
		motor_no_action_change(0, 0);
		if (Duration == 0 && SuperDuration == 0)
		{
			LED_1 = 0;
		}
		break;
	case DEPOSIT_OBJ:
		motor_no_action_change(0, 0);
		LED_1 = 2;
		MyState = 0;
		LoadedObjects = 0;
		// loaded_objects全体の大きさ / loaded_objects[0]の大きさ
		resetLoadedObjects();

		motor_no_action_change(0, 0);
		//depo = 0;
		if (Duration == 0 && SuperDuration == 0)
		{
			LED_1 = 0;
		}
		else if (SuperDuration < 10)
		{
			WheelLeft = 4;
			WheelRight = 5;
		}
		else if (!BothColorJudge(object_box))
		{
			ERROR_MESSAGE("this robot is not in object_box", MODE_NORMAL);
			LoadedObjects = 6;
			Duration = 0;
			for (int i = 0; i < 3; i++)
			{
				loaded_objects[i] = 2;
			}
		}
		break;
	case TELEPORT:
		WheelLeft = 0;
		WheelRight = 0;
		LED_1 = 0;
		MyState = 0;
		LoadedObjects = 0;
		SuperDuration = 0;
		resetLoadedObjects();
		break;
	case TO_DEPOSIT: // world 1 only
	case MAY_SUPER_FIND:// world 2 only
	default:
		ERROR_MESSAGE("action is " + to_string(static_cast<int>(getAction())), MODE_NORMAL);
		break;
	}
	LOG_MESSAGE("World1 Loop End", MODE_NORMAL);
}

int Game0_Superteam::shouldTeleport(void)
{
	if (Time > 180 &&!IsOnDepositArea()) 
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void Game0_Superteam::taskOnTeleport(void)
{
	UserGame0::taskOnTeleport();
	LoadedObjects = 0;

	loaded_objects[0] = 0;
	loaded_objects[1] = 0;
	loaded_objects[2] = 0;
	loaded_objects[3] = 0;
	Teleport = 1;
	cout << "teleport " << endl;
}

