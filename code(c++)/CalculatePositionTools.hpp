// #ifndef CALCULATE_POSITION_TOOLS_H
// #define CALCULATE_POSITION_TOOLS_H
// #include "CospaceSettings.hpp"

// enum MapObjectNumber
// {
//     NOTHING,
//     WALL,
//     YELLOW,
//     DEPOSIT
// };

// class CalculatePosition
// {
// public:
//     void thread(void);
//     void calculate(int us_left, int us_front, int us_right, int compass);
//     void showCurrentMapPossibility();
//     void showMap();

// private:
//     const static int kMapWidth = 240;
//     const static int kMapHeight = 180;
//     const static int kDistanceFromUS = 5;
//     const static int kUSMeasurementLimit = 185;

//     enum MapInfo
//     {
//         Nothing = 0,
//         Yellow = 1,
//         Wall = 2,
//         Deposit = 3
//     };

//     int equation[11][4] = {
//         {0, 0, 0, 180},
//         {0, 0, 240, 0},
//         {0, 180, 240, 180},
//         {240, 0, 240, 180},
//         {90, 60, 120, 60},
//         {90, 90, 120, 90},
//         {60, 150, 90, 150},
//         {60, 150, 60, 180},
//         {90, 60, 90, 90},
//         {90, 150, 90, 180},
//         {120, 60, 120, 90}};
//     int equation_num = std::extent<decltype(equation), 0>::value;

//     int map_data[24][18] = {
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
//         {0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {1, 1, 1, 1, 1, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {1, 1, 1, 1, 1, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {1, 1, 1, 1, 1, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

//     const int map_data_width = std::extent<decltype(map_data), 0>::value;
//     const int map_data_height = std::extent<decltype(map_data), 1>::value;
//     const int map_data_scale = kMapWidth / map_data_width;

//     float map_possibility[kMapWidth][kMapHeight];
//     int current_map_possibility[kMapWidth][kMapHeight];
//     int min_distance_from_wall[kMapWidth][kMapHeight];
//     // width / 2    height / 2  compass / 3
//     // unsigned char distance_from_wall[kMapWidth / 2][kMapHeight / 2][360 / 3];

//     int calculated_x, calculated_y;

//     // 直線の壁を登録する
//     void setEquation(int x1, int y1, int x2, int y2);
//     // 長方形の壁を登録する
//     void setEquations(int x1, int y1, int x2, int y2);
//     // (ax, ay), (bx, by)の線分上に(cx, cy)があるか
//     int judgeOnLineSegmenet(float ax, float ay, float bx, float by, float cx, float cy);
//     int isCross(int num, float x1, float y1, float x2, float y2);
// };

// #endif // CALCULATE_POSITION_TOOLS
