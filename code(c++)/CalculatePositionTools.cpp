// #include "CalculatePositionTools.hpp"
// #include "LogErrorTools.hpp"
// #include "CommonTools.hpp"
// #include "CospaceSettings.hpp"

// // #include <stdio.h>
// // #include <stdlib.h>

// using std::cout;
// using std::endl;
// using std::extent;
// using std::setw;
// using std::string;
// using std::to_string;

// #define COSPACE_WIDTH 240
// #define COSPACE_HEIGHT 180

// #define POSSIBILITY_VALUE_MAX 10.0
// #define POSSIBILITY_VALUE_MIN 0.1

// #define NOTHING 0
// #define WALL 2
// #define YELLOW 1
// #define DEPOSIT 3

// void CalculatePosition::thread(void)
// {
//     ProcessingTime pt;
//     pt.start();
//     static int hi = 0;
//     if (hi >= kMapHeight)
//     {
//         return;
//     }
//     rep(wj, kMapWidth)
//     {
//         map_possibility[wj][hi] = 0;
//         current_map_possibility[wj][hi] = 0;
//         if (hi % 2 == 0 && wj % 2 == 0)
//         {
//             rep(angle, 120)
//             {
//                 int x[4], y[4];
//                 //, X, Y, min_distance = kUSMeasurementLimit;
//                 //, distance;
//                 x[0] = wj + cos(angle * 3 / 180 * PI) * kDistanceFromUS;
//                 y[0] = hi + sin(angle * 3 / 180 * PI) * kDistanceFromUS;
//                 x[1] = x[0] + cos(angle * 3 / 180 * PI) * kUSMeasurementLimit;
//                 y[1] = y[0] + sin(angle * 3 / 180 * PI) * kUSMeasurementLimit;
//                 if (x[0] == x[1] && y[0] == y[1])
//                 {
//                     logErrorMessage.errorMessage(getFuncName(__FUNCTION__) + "() : error x[0] == x[1] and y[0] == y[1]", MODE_NORMAL);
//                     // distance_from_wall[wj / 2][hi / 2][angle];
//                     return;
//                 }
//                 if (x[1] == x[0])
//                 {
//                     if (!(angle > 80 && angle < 90) && !(angle > 260 && angle < 280))
//                     {
//                         logErrorMessage.errorMessage(getFuncName(__FUNCTION__) + "() : error angle " + to_string(angle));
//                     }
//                 }
//                 rep(k, equation_num)
//                 {
//                     // 交差する場合
//                     if (isCross(k, x[0], y[0], x[1], y[1]))
//                     {
//                         x[2] = equation[k][0];
//                         x[3] = equation[k][2];
//                         y[2] = equation[k][1];
//                         y[3] = equation[k][3];
//                         // 交点 (X, Y) 線分の座標(x1, y1) (x2, y2)...
//                         // X = x1 + s(x2 - x1) = x3 + t(x4 - x3)
//                         // Y = y1 + s(y2 - y1) = y3 + s(y4 - y3)
//                         //  <=>
//                         // t(x4 - x3) = s(x2 - x1) + (x1 - x3)
//                         // t(y4 - y3) = s(y2 - y1) + (y1 - y3)
//                         // <=>
//                         // s(y2 - y1) * (x4 - x3) + (y1 - y3) * (x4 - x3)
//                         // = s(x2 - x1) * (y4 - y3) + (x1 - x3) * (y4 - y3)
//                         // <=>
//                         // s((y2 - y1) * (x4 - x3) - (x2 - x1) * (y4 - y3))
//                         // = (x1 - x3) * (y4 - y3) - (y1 - y3) * (x4 - x3)
//                         // <=>
//                         // (y2 - y1) * (x4 - x3) - (x2 - x1) * (y4 - y3) != 0のとき
//                         // s = ((x1 - x3) * (y4 - y3) - (y1 - y3) * (x4 - x3))
//                         // / ((y2 - y1) * (x4 - x3) - (x2 - x1) * (y4 - y3))
//                         // (y2 - y1) * (x4 - x3) - (x2 - x1) * (y4 - y3) == 0のとき
//                         // 両者は平行 or

//                         // ksi = (y4 - y3)(x4 - x1) - (x4 - x3)(y4 - y1)
//                         // float ksi = (equation[k][3] - equation[k][1]) * (equation[k][3] - x1) - (equation[k][3] - equation[k][1]) * (equation[k][3] - y1);
//                         // // delta = (y4 - y3)(x2 - x1) - (x4- x3)(y2 - y1)
//                         // float delta = (equation[k][3] - equation[k][1]) * (x2 - x1) - (equation[k][3] - equation[k][1]) * (y2 - y1);
//                         // // ramda = ksi / delta
//                         // float ramda = ksi / delta;
//                         // x = x1 + ramda * (x2 - x1);
//                         // y = y1 + ramda * (y2 - y1);
//                         // m1 = (y2 - y1) / (x2 - x1);
//                         // m2 = (equation[k][3] - equation[k][1]) / (equation[k][2] - equation[k][0]);
//                         // x = (m1 * x1 - y1 - m2 * equation[k][0] + equation[k][1]) / (m1 - m2);
//                         // y = (y2 - y1) / (x2 - x1) * (x - x1) + y1;
//                         // distance = pow(x - wj, 2) + pow(y - hi, 2);
//                         // if (min_distance > distance)
//                         // {
//                         //     min_distance = distance;
//                         // }
//                     }
//                 }
//                 // distance_from_wall[wj / 2][hi / 2][angle] = min_distance;
//             }
//         }
//     }
//     hi++;
//     cout << "calculate thread" << pt.end() << " ms" << endl;
// }

// void CalculatePosition::setEquation(int x1, int y1, int x2, int y2)
// {
//     equation[equation_num][0] = x1;
//     equation[equation_num][1] = y1;
//     equation[equation_num][2] = x2;
//     equation[equation_num][3] = y2;
//     equation_num++;
// }

// // 長方形で、壁を登録する
// void CalculatePosition::setEquations(int x1, int y1, int x2, int y2)
// {
//     // 左の縦棒
//     equation[equation_num][0] = x1;
//     equation[equation_num][1] = y1;
//     equation[equation_num][2] = x1;
//     equation[equation_num][3] = y2;
//     equation_num++;

//     // 下の横棒
//     equation[equation_num][0] = x1;
//     equation[equation_num][1] = y1;
//     equation[equation_num][2] = x2;
//     equation[equation_num][3] = y1;
//     equation_num++;

//     // 右の縦棒
//     equation[equation_num][0] = x2;
//     equation[equation_num][1] = y1;
//     equation[equation_num][2] = x2;
//     equation[equation_num][3] = y2;
//     equation_num++;

//     // 上の横棒
//     equation[equation_num][0] = x1;
//     equation[equation_num][1] = y2;
//     equation[equation_num][2] = x2;
//     equation[equation_num][3] = y2;
//     equation_num++;
// }

// // (ax, ay), (bx, by)の線分上に(cx, cy)があるか
// int CalculatePosition::judgeOnLineSegmenet(float ax, float ay, float bx, float by, float cx, float cy)
// {
//     float border = 0.00001;
//     float l1 = (bx - ax) * (bx - ax) + (by - ay) * (by - ay);
//     float l2 = (cx - ax) * (cx - ax) + (cy - ay) * (cy - ay);
//     float c = (bx - ax) * (cx - ax) + (by - ay) * (cy - ay);
//     return c >= 0 && PLUSMINUS(c * c, l1 * l2, border) && l1 >= l2;
// }

// int CalculatePosition::isCross(int num, float x1, float y1, float x2, float y2)
// {
//     // (x2 - x1)(y - y1) - (x - x1)(y2 - y1) = 0
//     // (y2 - y1)x - (x2 - x1)y - (y2 - y1)x1 + (x2 - x1)y1 = 0
//     float a1, b1, c1, a2, b2, c2;
//     a1 = (y2 - y1);
//     b1 = -(x2 - x1);
//     c1 = (x2 - x1) * y1 - (y2 - y1) * x1;
//     a2 = (equation[num][3] - equation[num][1]);
//     b2 = -(equation[num][2] - equation[num][0]);
//     c2 = -b2 * equation[num][1] - a2 * equation[num][0];
//     float result1 = a2 * x1 + b2 * y1 + c2;
//     float result2 = a2 * x2 + b2 * y2 + c2;

//     float result3 = a1 * equation[num][0] + b1 * equation[num][1] + c1;
//     float result4 = a1 * equation[num][2] + b1 * equation[num][3] + c1;

//     return (result1 * result2 < 0 && result3 * result4 < 0) ||
//            judgeOnLineSegmenet(x1, x2, y1, y2, equation[num][0], equation[num][1]) ||
//            judgeOnLineSegmenet(x1, x2, y1, y2, equation[num][1], equation[num][2]) ||
//            judgeOnLineSegmenet(equation[num][0], equation[num][1], equation[num][2], equation[num][3], x1, y1) ||
//            judgeOnLineSegmenet(equation[num][0], equation[num][1], equation[num][2], equation[num][3], x2, y2);
// }

// void CalculatePosition::calculate(int us_left, int us_front, int us_right, int compass)
// {
//     ProcessingTime pt;
//     pt.start();

//     // 数学での角度に変換
//     compass += 90;

//     logErrorMessage.logMessage(getFuncName(__FUNCTION__) + "(" + to_string(us_left) + "," + to_string(us_front) + "," + to_string(us_right) + "," + to_string(compass) + ") start", MODE_DEBUG);

//     float move_x, move_y;
//     {
//         int motor_speed = abs(WheelLeft) + abs(WheelRight);
//         motor_speed /= 2;
//         move_x = cos((double)(Compass + 90) / 180 * PI) * motor_speed;
//         move_y = sin((double)(Compass + 90) / 180 * PI) * motor_speed;
//         if (WheelLeft * WheelRight <= 0)
//         {
//             move_x = 0;
//             move_y = 0;
//         }
//         // move backward
//         else if (WheelLeft + WheelRight < 0)
//         {
//             move_x = -move_x;
//             move_y = -move_y;
//         }
//     }

//     double angle[3] = {45, 0, -45};
//     int distance[3] = {us_left, us_front, us_right};
//     // 0 : x, 1 : y
//     double coordinate[3][2];

//     rep(i, 3)
//     {
//         // 中心から超音波センサまでの距離
//         distance[i] += kDistanceFromUS;
//         angle[i] = static_cast<int>(compass + angle[i]) % 360;
//         coordinate[i][0] = cos(angle[i] / 180 * PI) * distance[i];
//         coordinate[i][1] = sin(angle[i] / 180 * PI) * distance[i];
//         logErrorMessage.logMessage("calculated wall position " + to_string(coordinate[i][0]) + " " + to_string(coordinate[i][1]), MODE_DEBUG);
//     }

//     // 0:上 1:左 2:下 3:右
//     int margin[4] = {0, 0, 0, 0};
//     rep(i, 3)
//     {
//         if (coordinate[i][1] > margin[0])
//         {
//             margin[0] = coordinate[i][1];
//         }
//         if (coordinate[i][0] < margin[1])
//         {
//             margin[1] = coordinate[i][0];
//         }
//         if (coordinate[i][1] < margin[2])
//         {
//             margin[2] = coordinate[i][1];
//         }
//         if (coordinate[i][0] > margin[3])
//         {
//             margin[3] = coordinate[i][0];
//         }
//     }

//     // +- 反転
//     margin[1] = -margin[1];
//     margin[2] = -margin[2];

//     rep(i, 4)
//     {
//         margin[i] -= 5;
//         if (margin[i] < 0)
//         {
//             margin[i] = 0;
//         }
//     }

//     string message = "calculated margin (top, left, down, right) = ";
//     rep(i, 4)
//     {
//         message += to_string(margin[i]) + " ";
//     }
//     logErrorMessage.logMessage(message, MODE_DEBUG);

//     // 上
//     rep(wj, kMapWidth)
//     {
//         for (int hi = kMapHeight - margin[0]; hi < kMapHeight; ++hi)
//         {
//             current_map_possibility[wj][hi] = 0;
//         }
//     }

//     // 左
//     rep(wj, margin[1])
//     {
//         rep(hi, kMapHeight)
//         {
//             current_map_possibility[wj][hi] = 0;
//         }
//     }

//     // 下
//     rep(wj, kMapWidth)
//     {
//         rep(hi, margin[2])
//         {
//             current_map_possibility[wj][hi] = 0;
//         }
//     }

//     // 右
//     for (int wj = kMapWidth - margin[3]; wj < kMapWidth; wj++)
//     {
//         rep(hi, kMapHeight)
//         {
//             current_map_possibility[wj][hi] = 0;
//         }
//     }

//     // double difference = SIZE;
//     for (int wi = 0; wi < kMapWidth; ++wi)
//     {
//         // int x = map_wi * map_data_scale + wi;
//         for (int hj = 0; hj < kMapHeight; ++hj)
//         {
//             int map_x = wi / map_data_scale;
//             int map_y = hj / map_data_scale;
//             if (map_data[map_x][map_y] == WALL)
//             {
//                 current_map_possibility[wi][hj] = 0;
//                 continue;
//             }
//             // 上 左 下 右
//             if (hj >= kMapHeight - margin[0] || wi < margin[1] || hj < margin[2] || wi > kMapWidth - margin[3])
//                 continue;
//             int complete[3] = {0, 0, 0};
//             current_map_possibility[wi][hj] = 0;

//             rep(i, 3)
//             {
//                 // ロボットから伸びる超音波の線のうち、x方向とy方向の長さを調べ、それぞれの長さを比例定数として誤差を決める
//                 double difference_x = 5; //fabs(coordinate[i][0]) / (fabs(coordinate[i][0]) + fabs(coordinate[i][1])) * 5;
//                 double difference_y = 5; //fabs(coordinate[i][1]) / (fabs(coordinate[i][0]) + fabs(coordinate[i][1])) * 5;
//                 if (coordinate[i][0] < 0)
//                 {
//                     difference_x = -difference_x;
//                 }
//                 if (coordinate[i][1] < 0)
//                 {
//                     difference_y = -difference_y;
//                 }
//                 double x_min = wi + coordinate[i][0] - difference_x;
//                 double y_min = hj + coordinate[i][1] - difference_y;
//                 double x_big = wi + coordinate[i][0] + difference_x;
//                 double y_big = hj + coordinate[i][1] + difference_y;
//                 rep(j, equation_num)
//                 {
//                     int result1 = isCross(j, wi, hj, x_min, y_min);
//                     int result2 = isCross(j, wi, hj, x_big, y_big);
//                     if (complete[i] == 0 && result1 == 0 && result2 == 1)
//                     {
//                         complete[i] = 1;
//                     }
//                     else if (result1 == 1 && result2 == 1)
//                     {
//                         complete[i] = -1;
//                         break;
//                     }
//                 }
//                 if (complete[i] == -1)
//                 {
//                     break;
//                 }
//             }

//             complete[0] += complete[1] + complete[2];

//             if (complete[0] < 2)
//             {
//                 current_map_possibility[wi][hj] = 0;
//             }
//             else if (complete[0] == 2)
//             {
//                 current_map_possibility[wi][hj] = POSSIBILITY_VALUE_MAX / 2;
//             }
//             else
//             {
//                 current_map_possibility[wi][hj] = POSSIBILITY_VALUE_MAX;
//             }
//         }
//     }

//     double k = 0.9;
//     rep(wj, kMapWidth)
//     {
//         rep(hi, kMapHeight)
//         {
//             int num = 1;
//             float add = map_possibility[wj][hi];
//             int left = wj - move_x, right = wj;
//             int under = hi - move_y, top = hi;
//             if (left > right)
//             {
//                 int temp = left;
//                 left = right;
//                 right = temp;
//             }
//             if (under > top)
//             {
//                 int temp = under;
//                 under = top;
//                 top = temp;
//             }
//             // printf("%d %d %d %d\n", left, right, under, top);
//             for (int wj_range = left; wj_range <= right; wj_range++)
//             {
//                 for (int hi_range = under; hi_range <= top; hi_range++)
//                 {

//                     if (hi_range < 0 || hi_range >= kMapHeight || wj_range < 0 || wj_range >= kMapWidth)
//                     {
//                         continue;
//                     }
//                     num++; // 距離の二乗に反比例
//                     // addの合計値に反比例
//                     // 可能性が同じものが多い場合は、加える可能性を低くする
//                     add += (float)map_possibility[wj_range][hi_range];
//                 }
//             }
//             add = add / num;
//             current_map_possibility[wj][hi] = static_cast<int>(current_map_possibility[wj][hi] * (1.0 - k) + add * k);
//             // printf("%f\n", add);
//         }

//         // printf("%d calculated %d %d\n", getRepeatedNum(), x * SIZE, y * SIZE);
//     }
//     float min = 1000000, max = 0;
//     int max_id = -1;
//     rep(wj, kMapWidth)
//     {
//         rep(hi, kMapHeight)
//         {
//             int map_x = wj / map_data_scale;
//             int map_y = hi / map_data_scale;
//             if (map_data[map_x][map_y] == WALL)
//             {
//                 continue;
//             }
//             if (current_map_possibility[wj][hi] < min)
//             {
//                 min = current_map_possibility[wj][hi];
//             }
//             if (current_map_possibility[wj][hi] > max)
//             {
//                 max = current_map_possibility[wj][hi];
//                 max_id = hi * kMapWidth + wj;
//             }
//         }
//     }

//     // magnificationで、値の広さを調整する
//     // correctionで、値の位置を調整する
//     float magnification = POSSIBILITY_VALUE_MAX / (max - min);
//     float correction = POSSIBILITY_VALUE_MIN - min * magnification;
//     rep(wj, kMapWidth)
//     {
//         rep(hi, kMapHeight)
//         {
//             int map_x = wj / map_data_scale;
//             int map_y = hi / map_data_scale;
//             if (map_data[map_x][map_y] == WALL)
//             {
//                 map_possibility[wj][hi] = 0;
//                 continue;
//             }
//             map_possibility[wj][hi] = current_map_possibility[wj][hi] * magnification + correction;
//         }
//     }

//     calculated_y = max_id / kMapWidth;
//     calculated_x = max_id - calculated_y * kMapWidth;

//     cout << "calculated " << calculated_x << " " << calculated_y << endl;
//     logErrorMessage.logMessage("calculated");

//     // rep(wi, kMapWidth)
//     // {
//     //     rep(hj, kMapHeight)
//     //     {
//     //         if (current_map_possibility[wi][hj] >= POSSIBILITY_VALUE_MAX / 2)
//     //         {
//     //             cout << "calculated " << wi << " " << hj << endl;
//     //         }
//     //     }
//     // }
// }

// void CalculatePosition::showCurrentMapPossibility()
// {
//     int scale = 10;
//     for (int hi = kMapHeight / scale - 1; hi >= 0; hi--)
//     {
//         rep(wj, kMapWidth / scale)
//         {
//             int map_x = wj * scale / map_data_scale;
//             int map_y = hi * scale / map_data_scale;
//             if (map_data[map_x][map_y] == WALL)
//             {
//                 cout << "###";
//                 continue;
//             }
//             int sum = 0;
//             rep(y, scale)
//             {
//                 rep(x, scale)
//                 {
//                     sum += current_map_possibility[wj * scale + x][hi * scale + y];
//                 }
//             }
//             sum /= scale;

//             cout << setw(3) << sum;
//         }
//         cout << endl;
//     }
//     cout << endl;
//     cout << endl;
// }

// void CalculatePosition::showMap()
// {
//     int scale = 10;
//     for (int hi = kMapHeight / scale - 1; hi >= 0; hi--)
//     {
//         rep(wj, kMapWidth / scale)
//         {
//             int map_x = wj * scale / map_data_scale;
//             int map_y = hi * scale / map_data_scale;
//             if (map_data[map_x][map_y] == WALL)
//             {
//                 cout << "###";
//                 continue;
//             }
//             double max = 0;
//             rep(y, scale)
//             {
//                 rep(x, scale)
//                 {
//                     if (map_possibility[wj * scale + x][hi * scale + y] > max)
//                     {
//                         max = map_possibility[wj * scale + x][hi * scale + y];
//                     }
//                 }
//             }

//             cout << setw(3) << static_cast<int>(max);
//         }
//         cout << endl;
//     }
//     cout << endl;
//     cout << endl;
// }
