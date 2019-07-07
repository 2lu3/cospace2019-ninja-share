/*
todo:
JudgeColorTools.cppの色のデータの確認
特に、収集箱と罠は必ず確認すること

todo:
LOG_MESSAGE、ERROR_MESSAGEはC:\Microsoft Robotics Dev Studio 4の下にできる

todo:
main.cppで、Game1_Masuda game1;がコメントアウトされていないかを確認する

todo:
マップの図を書いて、どのような移動経路にするのかを決める
必ず、目的地を丸として、丸同士をつなぐ経路を矢印で示し、各目的地のprocessの番号と、座標を記入すること
頭の中で補完すると、必ずバグが生じる


*/
#include "Masuda.hpp"
#include <iostream>

#define IF if
#define LOG_MESSAGE(MESSAGE, OPTION) \
	IF((OPTION) <= getRunMode()) { logErrorMessage.logMessage((MESSAGE), (OPTION)); }
#define ERROR_MESSAGE(MESSAGE, OPTION) \
	IF((OPTION) <= getRunMode()) { logErrorMessage.errorMessage((MESSAGE), (OPTION)); }

#define FUNC_NAME getFuncName(__FUNCTION__)

using namespace std;

void Game0_Masuda::setup(void)
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

void Game0_Masuda::loop(void)
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
	else if (IsOnDepositArea() && LoadedObjects >= 1)
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
			SuperDuration = 65;

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
	}else if (depo == -1)
	{
		if (compassJudge(-15, 15)) {
			if (US_Front < 10) {
				//真下にBOXがある
				depo = 2;
			}
			else {
				//WにBOXがある
				depo = 1;
			}
		}
		else if (compassJudge(0, 90)) {
			motor(2, -2);
		}
		else if (compassJudge(90, 180)) {
			motor(2, -2);
		}
		else if (compassJudge(180, 270)) {
			motor(-2, 2);
		}
		else if (compassJudge(270, 360)) {
			motor(-2, 2);
		}
	}
	
	else if (depo == 1) {
		if (compassJudge(55, 75)) {
			// if (US_Front < 25) {
			// 	depo = 0;
			// }
			// else {
			// 	depo = 4;
			// }
			depo = 4;
		}
		else if (compassJudge(65, 245)) {
			motor(3, -3);
		}
		else {
			motor(-3, 3);
		}
	}
	else if (depo == 2) {
		if (compassJudge(170, 190)) {
			if (US_Front < 25) {
				depo = 0;
			}
			else {
				depo = 3;
			}
		}
		else if (compassJudge(180, 360)) {
			motor(3, -3);
		}
		else {
			motor(-3, 3);
		}
	}
	else if (depo == 3) {
		if (compassJudge(175, 185)) {
			if (US_Front < 5) {
				depo = 0;
			}
			motor(3, 3);
		}
		else if (compassJudge(180, 360)) {
			motor(3, 1);
		}
		else {
			motor(1, 3);
		}
	}
	else if (depo == 4) {
		//WのBOXに向かっている

		// if (US_Front < 5) {
		// 	depo = 0;
		// }
		if (compassJudge(60, 70)) {
			motor(3, 3);
		}
		else if (compassJudge(-115, 65)) {
			motor(1, 3);
		}
		else {
			motor(3, 1);
		}
	}
	else if (
	IsOnWorld1MakerArea() &&
		(LoadedObjects >= 5 || 
		(
		(loaded_objects[RED_LOADED_ID] > 0 && loaded_objects[CYAN_LOADED_ID] > 0 && loaded_objects[BLACK_LOADED_ID] > 0)
		&& should_deposit
		)
		||(Time>165 &&Time<175))
		) {
			depo = -1;
		// if (compassJudge(-15, 15)) {
		// 	if (US_Front < 10) {
		// 		//真下にBOXがある
		// 		depo = 2;
		// 	}
		// 	else {
		// 		//WにBOXがある
		// 		depo = 1;
		// 	}
		// }
		// else if (compassJudge(0, 90)) {
		// 	motor(2, -2);
		// }
		// else if (compassJudge(90, 180)) {
		// 	motor(2, -2);
		// }
		// else if (compassJudge(180, 270)) {
		// 	motor(-2, 2);
		// }
		// else if (compassJudge(270, 360)) {
		// 	motor(-2, 2);
		// }
	}else if (
		LoadedObjects >= 5||
		(
			loaded_objects[RED_LOADED_ID] > 0 && loaded_objects[CYAN_LOADED_ID] > 0 && loaded_objects[BLACK_LOADED_ID] > 0
		)
		||(Time>150 &&Time<175)
		)
	{
		LOG_MESSAGE("deposit", MODE_NORMAL);
		if (US_Front < 10)
		{
			motor(-3, 3);
		}
		else if (US_Right < 10)
		{
			motor(-3, -1);
		}
		else if (US_Right < 15)
		{
			motor(3, 4);
		}
		else if (US_Right < 20)
		{
			motor(4, 4);
		}
		else if (US_Right < 30)
		{
			motor(3, 2);
		}
		else if (US_Right < 50)
		{
			motor(4, 2);
		}
		// else if (US_Right > 80 && US_Right < 100 && US_Front >70)
		// {
		// 	motor(5, 5);
		// }
		else
		{
			motor(4, 2);
		}
	}
	
	else if (compassJudge(220,320) || compassJudge(45,135))
	{
		// if (US_Front < 30 && US_Left < 15 && US_Right < 15 && compassJudge(240, 300))
		// {
		// 	motor(-1, -2);
		// }

		// else 
		if (US_Front < 14)
		{
			motor(-2, 1);
		}
		else if (US_Left < 5)
		{
			motor(-1, -2);
		}
		else if (US_Right < 5)
		{
			motor(-2, -1);
		}
		else if (US_Right < 25) {
			motor(3, 5);
		}
		else if (US_Right < 35 + (deposit_num % 2) * 10 +  static_cast<int>(rnd()) % 10)
		{
			motor(2, 4);
		}
		else if (US_Right < 60 + (deposit_num % 2) * 10 +  static_cast<int>(rnd()) % 10)
		{
			motor(5, 3);
		}
		else if (US_Right < 90)
		{
			motor(5, 1);
		}
		
		else
		{
			motor(4, 3);
		}
	}else
	{
		if (US_Front < 10)
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
			motor(4, 2);
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
		depo = 0;
		if (Duration == 0 && SuperDuration == 0)
		{
			LED_1 = 0;
		}
		else if (SuperDuration < 15)
		{
			WheelLeft = 5;
			WheelRight = 4;
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

int Game0_Masuda::shouldTeleport(void)
{
	if (Time > 180 &&!IsOnDepositArea()&&!(depo!= 0&&(loaded_objects[RED_LOADED_ID] > 0 && loaded_objects[CYAN_LOADED_ID] > 0 && loaded_objects[BLACK_LOADED_ID] > 0))) 
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void Game0_Masuda::taskOnTeleport(void)
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

void Game1_Masuda::setup(void)
{
	system("cls");
	/*
	todo:
	エラーが起きた時にチェックする場所
	 */
	UserGame1::setup();
	// 文字コードをUTF-8に
	// Shift-JISは
	system("chcp 65001");
	// 初期位置がPositionLostAreaのとき
	if (PositionX == 0 && PositionY == 0)
	{
		/*
		todo: emergency_xとyに安全な値を入力する
		壁じゃなくて、罠でもなく、沼地でもない場所
		 */
		log_x = emergency_x;
		log_y = emergency_y;
	}
	else
	{
		log_x = PositionX;
		log_y = PositionY;
	}

	setRunMode(MODE_MATCH);
}

void Game1_Masuda::loop()
{
	ProcessingTime pt;
	pt.start();
	intrap();
	UserGame1::loop();

	if (PositionX != 0 || PositionY != 0)
	{
		log_x = PositionX;
		log_y = PositionY;

		if (log_x < 0)
		{
			log_x = 0;
		}
		if (log_x >= kCospaceWidth)
		{
			log_x = kCospaceWidth - 1;
		}
		if (log_y < 0)
		{
			log_y = 0;
		}
		if (log_y >= kCospaceHeight)
		{
			log_y = kCospaceHeight - 1;
		}
	}
	else
	{
		PositionX = -1;
	}

	if (SuperObj_Num != 0)
	{
		if (log_superobj_num <= 0 && (log_superobj_x[0] != SuperObj_X || log_superobj_y[0] != SuperObj_Y))
		{
			//I separate this from *1 because log_superobj_x[0 - 1] makes error
			log_superobj_x[0] = SuperObj_X;
			log_superobj_y[0] = SuperObj_Y;
			log_superobj_num++;
		}
		else
		{
			//*1
			//This avoid record same data many times
			// if the new SuperObject is undefined
			// hint : if log_superobj_num == 0, this doesn't work. so I separate this case
			if (log_superobj_x[log_superobj_num - 1] != SuperObj_X || log_superobj_y[log_superobj_num - 1] != SuperObj_Y)
			{
				log_superobj_x[log_superobj_num] = SuperObj_X;
				log_superobj_y[log_superobj_num] = SuperObj_Y;
				log_superobj_num++;
			}
		}
	}

	if (SuperDuration > 0)
	{
		SuperDuration--;
	}
	else if (IsOnRedObj() && LoadedObjects < 6 && loaded_objects[RED_LOADED_ID] < kBorderSameObjNum && !(LoadedObjects == 5 && log_superobj_num >= 1))
	{
		setAction(FIND_OBJ);
		loaded_objects[RED_LOADED_ID]++;
		SuperDuration = kFindObjDuration;
	}
	else if (IsOnCyanObj() && LoadedObjects < 6 && loaded_objects[CYAN_LOADED_ID] < kBorderSameObjNum && !(LoadedObjects == 5 && log_superobj_num >= 1))
	{
		setAction(FIND_OBJ);
		loaded_objects[CYAN_LOADED_ID]++;
		SuperDuration = kFindObjDuration;
	}
	else if (IsOnBlackObj() && LoadedObjects < 6 && loaded_objects[BLACK_LOADED_ID] < kBorderSameObjNum && !(LoadedObjects == 5 && log_superobj_num >= 1))
	{
		setAction(FIND_OBJ);
		loaded_objects[BLACK_LOADED_ID]++;
		SuperDuration = kFindObjDuration;
	}
	else if (IsOnSuperObj() && SuperObj_Num == 0 && log_superobj_num > 0 && !(IsOnRedObj() || IsOnBlackObj() || IsOnCyanObj()))
	{
		setAction(FIND_OBJ);
		SuperDuration = kFindObjDuration;
		int min = 10000;
		int num = 0;
		for (int i = 0; i < log_superobj_num; i++)
		{
			if (pow(log_superobj_x[i] - log_x, 2) + pow(log_superobj_y[i] - log_y, 2) < min)
			{
				min = static_cast<int>(pow(log_superobj_x[i] - log_x, 2) + pow(log_superobj_y[i] - log_y, 2));
				num = i;
			}
		}

		if (min < 1200)
		{
			//I delete log_superobj_x[2], I have to move the data of log_superobj_x[3] to [2].
			for (int i = num + 1; i < log_superobj_num; i++)
			{
				log_superobj_x[i] = log_superobj_x[i - 1];
				log_superobj_y[i] = log_superobj_y[i - 1];
			}
			loaded_objects[SUPER_LOADED_ID]++;
			log_superobj_num--;
		}
		else
		{
			motor(3, 3);
		}
	}
	else if (Duration > 0)
	{
		Duration--;
	}
	else if (IsOnYellowLine())
	{
		//motor(-5, -2);
		setAction(YELLOW_AVOIDANCE);
		Duration = 6;
	}
	else if (IsOnDepositArea() && (LoadedObjects >= 6 || (LoadedObjects > 0 && Time > 270)))
	{
		process = 0;
		if (IsOnDepositArea() == 3)
		{
			setAction(DEPOSIT_OBJ);
			Duration = kFindObjDuration;
		}
		else if (IsOnDepositArea() == 1)
		{
			motor(0, 5);
		}
		else
		{
			motor(5, 0);
		}
	}
	else
	{
		/*
		todo:
		分岐をする方法
		if (GoToPosition(275, 45, 5, 5, 5))
		{
			if(loaded_objects[0] < kBorderSameObjNum) {
				process ++;
			}
			else {
				process+=2;
			}
		}
		if (GoToPosition(275, 45, 5, 5, 5))
		{
			if(rnd() % 100) {
				process ++;
			}
			else {
				process+=2;
			}
		}if (GoToPosition(275, 45, 5, 5, 5))
		{
			if(loadedObject < 6) {
				process ++;
			}
			else {
				process+=2;
			}
		}
		todo:
		process文の最後に必ずelseを付けてprocessを定義する

		 */
		if (process == 0)
		{
			if (GoToPosition(275, 45, 5, 5, 5))
			{
				process++;
			}
		}
		else if (process == 1)
		{
			if (GoToPosition(210, 65, 0, 0, 5))
			{
				process++;
			}
		}
		else if (process == 2)
		{
			if (GoToPosition(180, 115, 0, 0, 5))
			{
				process++;
			}
		}
		else
		{
			process = 0;
		}
	}

	switch (static_cast<int>(getAction()))
	{
	case DEFINED:
		//defined motor power by motor(int left, int right)
		break;
	case FIND_OBJ:
		if (Duration == kFindObjDuration || SuperDuration == kFindObjDuration)
		{
			LoadedObjects++;
		}
		LED_1 = 1;
		MyState = 0;
		WheelLeft = 0;
		WheelRight = 0;
		if (Duration == 0 && SuperDuration == 0)
		{
			LED_1 = 0;
		}
		break;
	case DEPOSIT_OBJ:
		WheelLeft = 0;
		WheelRight = 0;
		LED_1 = 2;
		MyState = 0;
		LoadedObjects = 0;
		//initialize all value of loaded_objects
		for (int i = 0; i < 4; i++)
		{
			loaded_objects[i] = 0;
		}
		if (Duration == 0 && SuperDuration == 0)
		{
			LED_1 = 0;
		}
		else
		{
			if (!(IsOnDepositArea() == 3))
			{
				LoadedObjects = 6;
				Duration = 0;
				SuperDuration = 0;
				for (int i = 0; i < 3; i++)
				{
					loaded_objects[i] = 2;
				}
			}
		}
		break;
	default:
		printf("World2System(): action's value is ubnormal\n");
		break;
	}

	//This is for superobj
	//When there is no superobj, I give up to search superobj
	super_sameoperate++;
	if (log_superobj_num == 0)
	{
		super_sameoperate = 0;
	}
	if (super_sameoperate > 800)
	{
		log_superobj_num = 0;
		super_sameoperate = 0;
	}
	double seconds = pt.end();
	LOG_MESSAGE("loop time :" + to_string(seconds) + " ms", MODE_NORMAL);
}

long Game1_Masuda::WhereIsMotor(void)
{
	//fprintf(logfile, "%4d Start WhereIsMotor()\n", getRepeatedNum());
	long x, y;
	if (log_x < 0 || log_x >= kCospaceWidth || log_y < 0 || log_y >= kCospaceHeight)
	{
		//fprintf(errfile, "%4d WhereIsMotor(): log_x, log_y = (%d, %d)\n", getRepeatedNum(), log_x, log_y);
		//fprintf(logfile, "%4d WhereIsMotor(): log_x, log_y = (%d, %d)\n", getRepeatedNum(), log_x, log_y);
		log_x = kCospaceWidth / 2;
		log_y = kCospaceHeight / 2;
	}
	x = log_x - static_cast<long>(cos((Compass + 90) * 3.14 / 180)) * 5;
	y = log_y - static_cast<long>(sin((Compass + 90) * 3.14 / 180)) * 5;
	//fprintf(logfile, "%4d End WhereIsMotor() with returning %ld * 1000 + %ld = %ld\n", getRepeatedNum(), y, x, y * 1000 + x);
	return y * 1000 + x;
}
long Game1_Masuda::WhereIsColorSensor(void)
{
	long x, y;
	if (log_x < 0 || log_x >= kCospaceWidth || log_y < 0 || log_y >= kCospaceHeight)
	{
		log_x = kCospaceWidth / 2;
		log_y = kCospaceHeight / 2;
	}
	x = log_x + static_cast<long>(cos((Compass + 90) * 3.14 / 180) * 5);
	y = log_y + static_cast<long>(sin((Compass + 90) * 3.14 / 180) * 5);
	if (x < 0)
	{
		x = 0;
	}
	if (y < 0)
	{
		y = 0;
	}
	if (x >= kCospaceWidth)
	{
		x = kCospaceWidth - 1;
	}
	if (y >= kCospaceHeight)
	{
		y = kCospaceHeight - 1;
	}
	return y * 1000 + x;
}

int Game1_Masuda::GoToPosition(int x, int y, int wide_decide_x, int wide_decide_y, int wide_judge_arrived)
{
	LOG_MESSAGE(FUNCNAME + "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(wide_decide_x) + ", " + to_string(wide_decide_y) + ", " + to_string(wide_judge_arrived) + "): start", MODE_DEBUG);
	static int absolute_x = -1;
	static int absolute_y = -1;
	static int absolute_distance = -1;
	static int same_operate = -1;

	static int repeated_num_log = -1;
	static int objects_num_log = -1;
	if (repeated_num_log == -1)
	{
		repeated_num_log = getRepeatedNum() - 1;
		objects_num_log = LoadedObjects;
	}

	//引数の値がおかしい場合
	if (x < 0 || y < 0 || x > kCospaceWidth || y > kCospaceHeight || wide_decide_x < 0 || wide_decide_y < 0 || wide_judge_arrived < 0)
	{
		printf("GoToPosition(): 引数が(%d, %d, %d, %d, %d)\n", x, y, wide_decide_x, wide_decide_y, wide_judge_arrived);
		return 0;
	}

	//absolute_x,yの値が、x, yの値からずれている場合
	if (absolute_x == -1 || !(PLUSMINUS(absolute_x, x, wide_decide_x) && PLUSMINUS(absolute_y, y, wide_decide_y)))
	{
		int i = 0;
		do
		{
			if (i > 20)
			{
				absolute_x = x;
				absolute_y = y;
				ERROR_MESSAGE("warming GoToPosition(): absolute_x, absolute_yが決まりません; (" + to_string(x) + ", " + to_string(y) + ", " + to_string(wide_decide_x) + ", " + to_string(wide_decide_y) + ", " + to_string(wide_judge_arrived) + ")", MODE_NORMAL);
				break;
			}
			absolute_x = x - wide_decide_x + (rnd() + 1) % (wide_decide_x * 2 + 1);
			absolute_y = y - wide_decide_y + (rnd() + 1) % (wide_decide_y * 2 + 1);
			i++;
		} while (absolute_x < 10 || absolute_x > kCospaceWidth - 10 || absolute_y < 10 || absolute_y > kCospaceHeight - 10);
		//same_operate = 0;
	}

	if (absolute_distance <= -1)
	{
		absolute_distance = static_cast<int>(sqrt(pow(absolute_x - log_x, 2) + pow(absolute_y - log_y, 2))) + 40;
	}

	if (absolute_distance < same_operate)
	{
		printf("(%d, %d) arrive because too many same_operate\n", x, y);
		absolute_x = -1;
		absolute_y = -1;
		same_operate = -1;
		absolute_distance = -1;
		if (PositionX == -1)
		{
			log_x = x;
			log_y = y;
		}
		return 1;
	}

	int temp_x = WhereIsColorSensor();
	int temp_y = temp_x / 1000;
	temp_x -= temp_y * 1000;
	if (PLUSMINUS(absolute_x, temp_x, wide_judge_arrived) && PLUSMINUS(absolute_y, temp_y, wide_judge_arrived))
	{
		printf("(%d, %d)に到着しました\n", absolute_x, absolute_y);
		LOG_MESSAGE("(" + to_string(absolute_x) + "," + to_string(absolute_y) + ")に到着しました", MODE_NORMAL);
		absolute_x = -1;
		absolute_y = -1;
		same_operate = -1;
		absolute_distance = -1;
		return 1;
	}

	LOG_MESSAGE("ab(" + to_string(absolute_x) + "," + to_string(absolute_y) + ")", MODE_NORMAL);
	x = absolute_x;
	y = absolute_y;
	x = x - temp_x;
	y = y - temp_y;
	LOG_MESSAGE("x, y = " + to_string(x) + ", " + to_string(y), MODE_NORMAL);
	double angle = atan2(y, x);
	angle = angle * 180 / 3.14;
	int angle_int = static_cast<int>(angle);
	angle_int -= 90;
	if (angle_int < 0)
	{
		angle_int += 360;
	}
	LOG_MESSAGE("angle " + to_string(angle_int), MODE_NORMAL);
	GoToAngle(angle_int, static_cast<int>(sqrt(x * x + y * y)));

	if (repeated_num_log + 1 == getRepeatedNum() && objects_num_log != LoadedObjects)
	{
		same_operate++;
	}
	else
	{
		same_operate = 0;
	}
	repeated_num_log = getRepeatedNum();

	return 0;
}

void Game1_Masuda::GoToAngle(int angle, int distance)
{
	/*
	・壁を自動でよける
	・沼の中ではスピードを極力上げる
	・distanceの距離によってその場所に正確に移動する
	→二つのカラーセンサの丁度中心が目的地に重なるように動く
	・distanceの単位はcm(つまりx,yが1つづつ)
	 */
	LOG_MESSAGE(FUNCNAME + "(" + to_string(angle) + "," + to_string(distance) + "): start", MODE_VERBOSE);
	angle = angle - Compass;

	angle %= 360;

	if (angle > 180)
	{
		angle -= 360;
	}
	if (angle < -180)
	{
		angle += 360;
	}

	int classification = obstacle(10, 12, 10);
	if (log_superobj_num > 0)
	{
		classification = obstacle(5, 7, 5);
	}

	int big_motor = 5;
	int short_motor = 3;
	switch (classification)
	{
	case 0:
		classification = obstacle(30, 40, 30);
		if (log_superobj_num > 0)
		{
			classification = obstacle(15, 20, 15);
		}
		if (classification == 1 && angle > 0 && angle < 90)
		{ //left
			// motor(5, short_left);
			motor(big_motor, short_motor);
		}
		else if (classification == 2 && abs(angle) < 30)
		{ //front
			if (angle < 0)
			{
				// motor(5, short_front);
				motor(big_motor, short_motor);
			}
			else
			{
				// motor(short_front, 5);
				motor(short_motor, big_motor);
			}
		}
		else if (classification == 3 && angle > -30 && angle < 90)
		{ //left & front
			//motor(5, (short_left < short_front) ? (short_left) : (short_right));
			motor(big_motor, short_motor);
		}
		else if (classification == 4 && angle < 0 && angle > -90)
		{ //right
			//motor(short_right, 5);
			motor(short_motor, big_motor);
		}
		else if (classification == 5 && abs(angle) > 30)
		{ //left & right
			if (abs(angle) < 150)
			{
				motor(big_motor, big_motor);
				//motor(5, 5);
			}
			else
			{
				if (angle < 0)
				{
					motor(3, -4);
				}
				else
				{
					motor(-4, 3);
				}
				// Duration = 5;
			}
		}
		else if (classification == 6 && angle < 30 && angle > -90)
		{ //front & right
			//motor((short_right < short_front) ? (short_right) : (short_right), 5);
			motor(short_motor, big_motor);
		}
		else if (classification == 7)
		{ //all
			if (angle < 0)
			{
				//motor(5, short_front);
				motor(big_motor, short_motor);
			}
			else
			{
				//motor(short_front, 5);
				motor(short_motor, big_motor);
			}
		}
		else
		{
			if (IsOnSwampland())
			{
				if (abs(angle) < 30)
				{
					motor(5, 5);
				}
				else if (abs(angle) < 90)
				{
					if (angle < 0)
					{
						motor(5, 1);
					}
					else
					{
						motor(1, 5);
					}
				}
				else
				{
					if (angle < 0)
					{
						motor(5, -5);
					}
					else
					{
						motor(-5, 5);
					}
				}
				Duration = 5;
			}
			else
			{
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
						motor(4, -5);
					}
					else
					{
						motor(-5, 4);
					}
					// Duration = 3;
				}
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
		if (CurGame == 0)
		{
			motor(3, 3);
		}
		else
		{
			motor(-2, -3);
		}
		break;
	case 7: //left front right
		motor(-3, -3);
		break;
	default:
		break;
	}
}
