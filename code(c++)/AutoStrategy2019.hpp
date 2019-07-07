#ifndef AUTO_STRATEGY2019_HPP
#define AUTO_STRATEGY2019_HPP

#include "CospaceSettings.hpp"
#include "CommonTools.hpp"
#include <climits>
#include <random>

class AutoStrategy : public UserGame1
{
public:
    AutoStrategy();
    ~AutoStrategy() override;
    void setup() override;
    void loop() override;

private:
    const static int kCospaceWidth = 360;
    const static int kCospaceHeight = 270;
    const static int kCM2DotScale = 10;
    const static int kDotWidth = kCospaceWidth / kCM2DotScale;
    const static int kDotHeight = kCospaceHeight / kCM2DotScale;
	/*const static int kCM2SecureAreaScale = 30;
	const static int kSecureAreaWidth = kCospaceWidth / kCM2SecureAreaScale;
	const static int kSecureAreaHeight = kCospaceHeight / kCM2SecureAreaScale;*/
    const static int kCM2AreaScale = 30;
    const static int kDot2AreaScale = kCM2AreaScale / kCM2DotScale;
    const static int kAreaWidth = kCospaceWidth / kCM2AreaScale;
    const static int kAreaHeight = kCospaceHeight / kCM2AreaScale;
	const static int kUSLimit = 186;

    const int kBorderSameObjNum = 2;
    const int kFindObjDuration = 45;
    const int kDepositObjDuration = 45;
    const int kProcessingNumOfOneThread = 90;
    const int kThreadNum = static_cast<int>((kDotHeight + kProcessingNumOfOneThread - 1) / kProcessingNumOfOneThread);

    int log_superobj_num, log_superobj_x[10], log_superobj_y[10];
    long same_time, super_sameoperate;
    int process;
    int searching_object;
    int prev_repeated_num;

    std::random_device rnd;

    int kEmergencyPosX = 180;
    int kEmergencyPosY = 135;

    ProcessingTime pt;

    class CospaceMap
    {
    public:
        CospaceMap();
        enum MapInfo
        {
            MAP_FAILURE = -1000,
            MAP_SUCCESS = -1001,
            MAP_YELLOW = 0,    // カラーセンサーの値によって決まる
            MAP_SWAMPLAND = 1, // カラーセンサーの値によって決まる
            MAP_UNKNOWN = 2, // 不明な場合
            MAP_WALL = 3,
            MAP_WHITE = 4,      // カラーセンサーの値によって決まる
            MAP_DEPOSIT = 5,    // カラーセンサーの値によって決まる
            MAP_SUPER_AREA = 6, // カラーセンサーの値によって決まる
        };
        inline int setMapInfo(int x, int y, MapInfo info)
        {
            return setMapInfo(x, y, info, 1);
        }
        inline int setMapInfo(int x, int y, MapInfo info, int times)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            if (info == MAP_WALL)
            {
                map[map_wall_index][y][x] = times;
            }
            else if (info == MAP_WHITE && (map[0][y][x] != MAP_UNKNOWN && map[0][y][x] != MAP_SWAMPLAND))
            {
                return kFailure;
            }
            else if (info == MAP_SWAMPLAND && map[0][y][x] != MAP_UNKNOWN)
            {
                return kFailure;
            }
            else
            {
                // if(map[0][y][x] == MAP_UNKNOWN) {
                //     map[0][y][x] = info;
                // }
                // else {
                //     map[0][y][x] = info;
                // }
                map[0][y][x] = info;
            }
            return kSuccess;
        }
        inline int setMapInfoForce(int x, int y, MapInfo info)
        {
            return setMapInfoForce(x, y, info, 1);
        }
        inline int setMapInfoForce(int x, int y, MapInfo info, int times)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            if (info == MAP_WALL)
            {
                map[map_wall_index][y][x] = times;
            }
            else
            {
                map[0][y][x] = info;
            }
            return kSuccess;
        }
        inline int addMapInfo(int x, int y, MapInfo info)
        {
            return setMapInfo(x, y, info, 1);
        }
        inline int addMapInfo(int x, int y, MapInfo info, int times)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            if (info == MAP_WALL)
            {
                map[map_wall_index][y][x] += times;
            }
            else
            {
                // if(map[0][y][x] == MAP_UNKNOWN) {
                //     map[0][y][x] = info;
                // }
                // else {
                //     map[0][y][x] = info;
                // }
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + "(): warming; you should use setMapInfo() instead of " + FUNCNAME + "() if you don't want to change the value of MAP_WALL", MODE_NORMAL);
                }
                map[0][y][x] = info;
            }
            return kSuccess;
        }
        inline MapInfo getMapInfo(int x, int y)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return MAP_FAILURE;
            }
            if (map[map_wall_index][y][x] > 0)
            {
                return MAP_WALL;
            }
            else
            {
                return static_cast<MapInfo>(map[0][y][x]);
            }
            return MAP_SUCCESS;
        }
        inline int setMapObjInfo(int x, int y, int object_loaded_id)
        {
            return setMapObjInfo(x, y, object_loaded_id, 1);
        }
        inline int setMapObjInfo(int x, int y, int object_loaded_id, int value)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            if (object_loaded_id != RED_LOADED_ID && object_loaded_id != CYAN_LOADED_ID && object_loaded_id != BLACK_LOADED_ID)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; object_loaded_id = " + std::to_string(object_loaded_id), MODE_NORMAL);
                }
                return kFailure;
            }
            if (object_loaded_id <= 0 || object_loaded_id >= static_cast<int>((std::extent<decltype(map), 0>::value)))
            {
                if (MODE_VERBOSE <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; object_loaded_id = " + std::to_string(object_loaded_id), MODE_VERBOSE);
                }
                return kFailure;
            }
            map[object_loaded_id][y][x] = value;
            return kSuccess;
        }
        inline int getMapObjInfo(int x, int y, int object_loaded_id)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            if (object_loaded_id != RED_LOADED_ID && object_loaded_id != CYAN_LOADED_ID && object_loaded_id != BLACK_LOADED_ID)
            {
                if (MODE_VERBOSE <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; object_loaded_id = " + std::to_string(object_loaded_id), MODE_VERBOSE);
                }
                return kFailure;
            }
            if (object_loaded_id <= 0 || object_loaded_id >= static_cast<int>(std::extent<decltype(map), 0>::value))
            {
                if (MODE_VERBOSE <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; object_loaded_id = " + std::to_string(object_loaded_id), MODE_VERBOSE);
                }
                return kFailure;
            }
            return map[object_loaded_id][y][x];
        }
        inline int addMapArrivedTimes(int x, int y, int times)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            map_arrived_times[y][x] += times;
            return kSuccess;
        }
        inline int addMapArrivedTimes(int x, int y)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            return addMapArrivedTimes(x, y, 1);
        }
        inline int getMapArrivedTimes(int x, int y)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            return map_arrived_times[y][x];
        }
        inline int setMapArrivedTimes(int x, int y, int value)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            map_arrived_times[y][x] = value;
        }
        inline int setMapFrom(int x, int y, int from_x, int from_y)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            map_from[y][x][0] = from_x;
            map_from[y][x][1] = from_y;
            return kSuccess;
        }
        inline int getMapFrom(int x, int y, int *from_x, int *from_y)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            *from_x = map_from[y][x][0];
            *from_y = map_from[y][x][1];
            return kSuccess;
        }
        inline int setMapCost(int x, int y, int cost)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            map_cost[y][x] = cost;
            return kSuccess;
        }
        inline int getMapCost(int x, int y)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            return map_cost[y][x];
        }
        inline int setMapTotalCost(int x, int y, int cost)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            map_total_cost[y][x] = cost;
            return kSuccess;
        }
        inline int getMapTotalCost(int x, int y)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            return map_total_cost[y][x];
        }
        inline int setMapStatus(int x, int y, int status)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            map_status[y][x] = status;
            return kSuccess;
        }
        inline int getMapStatus(int x, int y)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            return map_status[y][x];
        }
        inline int setMapCurvedTimes(int x, int y, int value)
        {
            if (x < 0 || x >= kDotWidth || y < 0 || y >= kDotHeight)
            {
                if (MODE_NORMAL <= getRunMode())
                {
                    logErrorMessage.errorMessage(FUNCNAME + " Failed; (x, y)=(" + std::to_string(x) + ", " + std::to_string(y) + ")", MODE_NORMAL);
                }
                return kFailure;
            }
            map_curved_times[y][x] = value;
            return kSuccess;
        }
        int getMapCurvedTimes(int from_x, int from_y, int target_x, int target_y);

        const static int kSuccess = -1;
        const static int kFailure = INT_MIN;
        const static int kGuessedMapSize = 10;

    private:
        const static int map_wall_index = 4;
        // 0:床情報 1:red 2:cyan 3:black 4:壁情報
        int map[5][kDotHeight][kDotWidth];
        int map_arrived_times[kDotHeight][kDotWidth];
        int map_from[kDotHeight][kDotWidth][2];
        int map_cost[kDotHeight][kDotWidth];
        int map_total_cost[kDotHeight][kDotWidth];
        int map_status[kDotHeight][kDotWidth];
        int map_curved_times[kDotHeight][kDotWidth];
		//int map_secure[7][kSecureAreaHeight][kSecureAreaWidth];
    };
    CospaceMap cospaceMap;

    int pos_x,
        pos_y,
        pos_compass;
    long robot_dot_positions[3][2];

    long now_dot_id;

    void CheckNowDot();
    void GoToAngle(int angle, int distance);
    int GoToPosition(int x, int y, int wide_decide_x, int wide_decide_y, int wide_judge_arrived);
    void Dijkstra(void);
    void Astar(int goal_x, int goal_y);
    int GoToDot(int x, int y);
    long WhereIsMotor(void);
    long WhereIsColorSensor(void);
    void InputDotInformation(void);
    int GoToDots(int x, int y, int wide_decide_x, int wide_decide_y);
    int GoInDots(int x, int y, int wide_decide_x, int wide_decide_y, int color);
    int HowManyCurved(int id);
    int isNearTheFloor(CospaceMap::MapInfo color, int x, int y, int cm_radius);
    void autoSearch(float parameter);
    void saveColorInfo(void);
    void calculateWallPosition(void);
    inline double sigmoid(double gain, double value, double scale)
    {
        return (1.0 / (1.0 + exp(-gain * value))) * scale;
    }
    inline double sigmoid(double value, double scale)
    {
        return sigmoid(1, value, scale);
    }
    inline int i_sigmoid(double gain, double value, double scale)
    {
        return static_cast<int>(sigmoid(gain, value, scale));
    }
    inline int i_sigmoid(double value, double scale)
    {
        return i_sigmoid(1, value, scale);
    }
};

#endif //!AUTO_STRATEGY_HPP
