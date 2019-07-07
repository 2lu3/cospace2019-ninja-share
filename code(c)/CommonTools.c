#include "CommonTools.h"
#include "CospaceSettings.h"

enum Action action;
enum Mode mode = MODE_NORMAL;
enum Mode default_mode = MODE_NORMAL;

int loaded_objects[4];
int repeated_num = 0;

void commonSetup0(void)
{
  srand((unsigned int)time(NULL));
  logErrorToolsSetup();
  judgeColorToolsSetup();
}

void commonLoopStart0(void)
{
}

void commonLoopEnd0(void)
{
  addRepeatedNum();
  if (CurAction == 1)
  {
    LoadedObjects = 0;
    for (unsigned int i = 0; i < sizeof(loaded_objects) / sizeof(*loaded_objects); i++)
    {
      loaded_objects[i] = 0;
    }
    resetRepeatedNum();
  }
}

void commonSetup1(void)
{
  LoadedObjects = 0;
  for (unsigned int i = 0; i < sizeof(loaded_objects) / sizeof(loaded_objects[0]); i++)
  {
    loaded_objects[i] = 0;
  }
}

void commonLoopStart1(void)
{
}

void commonLoopEnd1(void)
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

void setAction(enum Action pushed_action)
{
  action = pushed_action;
}

enum Action getAction(void)
{
  return action;
}

enum Mode getDefaultRunMode()
{
  return default_mode;
}

void setDefaultRunMode(enum Mode pushed_mode)
{
  default_mode = pushed_mode;
}

void setRunMode(enum Mode pushed_mode)
{
  mode = pushed_mode;
}

enum Mode getRunMode(void)
{
  return mode;
}
