#ifndef CALCULATE_POSITION_TOOLS
#define CALCULATE_POSITION_TOOLS
#include <math.h>
#include "CospaceSettings.h"

enum MapObjectNumber
{
  NOTHING,
  WALL,
  YELLOW,
  DEPOSIT
};

void showMap2();
void init();
void init2();

void setEquation(int x1, int y1, int x2, int y2);
// 長方形で、壁を登録する
void setEquations(int x1, int y1, int x2, int y2);

// (ax, ay), (bx, by)の線分上に(cx, cy)があるか
int judgeOnLineSegmenet(double ax, double ay, double bx, double by, double cx, double cy);
int isCross(int num, double x1, double y1, double x2, double y2);
void calculate2(int us_left, int us_front, int us_right, int compass);

#endif // CALCULATE_POSITION_TOOLS
