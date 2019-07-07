#include "odometory.h"
#include <math.h>

#define PI 3.14
/*
5 5 : 3
4 4 : 2.5
3 3 : 1.85
2 2 : 1.2
1 1 : 0.45
*/

float wheelpower2cm[11] = {-3, -2.5, -1.85, -1.2, -0.45, 0, 0.45, 1.2, 1.85, 2.5, 3};

void calculateOdometory(int wheelLeft, int wheelRight, int compass_before, int compass_after, float log_position[], float calculated_position[])
{
  float x1, y1, x2, y2;
  // 回転角
  float delta_theta = PI * (compass_after - compass_before) / 180;
  // 回転する前の角度
  float theta = PI * (compass_before - 90) / 180;
  // 左、右のモータ、ロボットの中央からの、回転の中心との距離
  float lenL, lenR, lenM;
  // 左、右のモーターの動いた距離
  float deltaL, deltaR;

  deltaL = wheelpower2cm[wheelLeft + 5];
  deltaR = wheelpower2cm[wheelRight + 5];

  lenL = deltaL / delta_theta;
  lenR = deltaR / delta_theta;
  lenM = (lenL + lenR) / 2;

  x1 = lenM * cos(theta);
  y1 = lenM * sin(theta);
  x2 = lenM * cos(theta + delta_theta);
  y2 = lenM * sin(theta + delta_theta);

  float x, y;
  x = x2 - x1;
  y = y2 - y1;

  calculated_position[0] = x + log_position[0];
  calculated_position[1] = y + log_position[1];
}
