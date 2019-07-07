#ifndef COMMON_TOOLS
#define COMMON_TOOLS

#include "CospaceSettings.h"
#include "LogErrorTools.h"
// #include "JudgeAngleTools.hpp"
#include "JudgeColorTools.h"
#include "CalculatePositionTools.h"
#include "odometory.h"

#define PI 3.14

// red cyan black super
#define RED_LOADED_ID 0
#define CYAN_LOADED_ID 1
#define BLACK_LOADED_ID 2
#define SUPER_LOADED_ID 3
extern int loaded_objects[4];

int getRepeatedNum(void);
void addRepeatedNum(void);
void resetRepeatedNum(void);
void motor(int left, int right);
void motor_no_action_change(int left, int right);
int obstacle(int left, int front, int right);

void commonSetup0(void);
void commonSetup1(void);
void commonLoopStart0(void);
void commonLoopEnd0(void);
void commonLoopStart1(void);
void commonLoopEnd1(void);

void setAction(enum Action pushed_action);
enum Action getAction(void);
enum Mode getDefaultRunMode();
void setDefaultRunMode(enum Mode pushed_mode);
void setRunMode(enum Mode pushed_mode);
enum Mode getRunMode(void);

#endif // !COMMON_TOOLS
