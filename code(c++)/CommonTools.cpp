#include "CommonTools.hpp"

using namespace std;

enum Action action;
enum Mode mode = MODE_NORMAL;
enum Mode default_mode = MODE_NORMAL;
bool is_output_log_message2console = false;
bool is_output_error_message2console = false;

int loaded_objects[4];
int repeated_num = 0;

std::random_device rnd;

UserGame0::~UserGame0()
{
}

void UserGame0::setup(void)
{
	InputColorInformation();
	resetRepeatedNum();
}

void UserGame0::loop(void)
{
	addRepeatedNum();
}

int UserGame0::shouldTeleport(void)
{
	return (Time > 180 && LoadedObjects < 2) || Time > 200;
}

void UserGame0::taskOnTeleport(void)
{
	resetRepeatedNum();
	WheelLeft = 0;
	WheelRight = 0;
	setAction(DEFINED);
	resetLoadedObjects();
	CurGame = 1;
	Teleport = 1;
}

/* int UserGame0::Isitbluerobot(int min ,int max,int front,int right,int left)//blueの方の情報を入力
{
	if (compassJudge(min,max)&&)
	{
		robot = 1;
		return robot_color;
		
	}else
	{
		robot = 0;
		return robot_color;
	}
	
	
	
}*/


UserGame1::~UserGame1()
{
}

void UserGame1::setup(void)
{
	InputColorInformation();
	resetRepeatedNum();
}

void UserGame1::loop(void)
{
	addRepeatedNum();
}

int getRepeatedNum(void)
{
	return repeated_num;
}

void addRepeatedNum(void)
{
	repeated_num++;
}

void resetRepeatedNum(void)
{
	repeated_num = 0;
}

void motor(int left, int right)
{
	WheelLeft = left;
	WheelRight = right;
	action = DEFINED;
	LED_1 = 0;
}

void motor_no_action_change(int left, int right)
{
	WheelLeft = left;
	WheelRight = right;
}

int obstacle(int left, int front, int right)
{
	int classification = 0;
	if (US_Left < left)
	{
		classification++;
	}
	if (US_Front < front)
	{
		classification += 2;
	}
	if (US_Right < right)
	{
		classification += 4;
	}
	return classification;
}

void ProcessingTime::start(void)
{
	start_time = chrono::system_clock::now();
}
int ProcessingTime::end(void)
{
	end_time = chrono::system_clock::now();
	int elapsed = static_cast<int>(chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
	return elapsed;
}
void ProcessingTime::print(string message)
{
	printf("%s %2dms\n", message.c_str(), end());
}
void ProcessingTime::print(void)
{
	print("");
}
/*
int deposittimetools::deposit()
 */
std::string getFuncName(const char *name)
{
	return name;
}

void setAction(Action pushed_action)
{
	action = pushed_action;
}

Action getAction(void)
{
	return action;
}

Mode getDefaultRunMode()
{
	return default_mode;
}

void setDefaultRunMode(Mode pushed_mode)
{
	default_mode = pushed_mode;
}

void setRunMode(Mode pushed_mode)
{
	mode = pushed_mode;
	logErrorMessage.logMessage("Set Run Mode as " + to_string(static_cast<int>(pushed_mode)), MODE_DEBUG);
}

Mode getRunMode(void)
{
	return mode;
}

bool getIsOutputLogMessage2Console(void)
{
	return is_output_log_message2console;
}
void setIsOutputLogMessage2Console(bool option)
{
	is_output_log_message2console = option;
}
bool getIsOutputErrorMessage2Console(void)
{
	return is_output_error_message2console;
}
void setIsOutputErrorMessage2Console(bool option)
{
	is_output_error_message2console = option;
}

void resetLoadedObjects(void)
{
	LoadedObjects = 0;
	for (int &loaded : loaded_objects)
	{
		loaded = 0;
	}
}

void intrap(void){
	if (IsOnTrapBlue())
	{
		resetLoadedObjects();
	}
	
	
}