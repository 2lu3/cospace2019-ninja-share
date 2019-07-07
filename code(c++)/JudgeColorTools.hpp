#ifndef JUDGE_COLOR_TOOLS
#define JUDGE_COLOR_TOOLS

#include "CospaceSettings.hpp"
#include "LogErrorTools.hpp"

extern int red_obj[3][2];
extern int cyan_obj[3][2];
extern int black_obj[3][2];
extern int trap_line[3][2];
extern int blue_zone[3][2];
extern int object_box[3][2];
extern int gray_zone[3][2];
extern int sp_obj[3][2];
extern int purple_line[3][2];
extern int white_zone[3][2];
extern int world1_maker[3][2];
extern int object_box2[3][2];
extern int blue_trap[3][2];

int ColorJudgeLeft(int col[3][2]);
int ColorJudgeRight(int col[3][2]);
int EitherColorJudge(int col[3][2]);
int BothColorJudge(int col[3][2]);

// 別バージョン
void InputColorInformation(void);
int IsOnYellowLine(void);
int IsOnRedObj(void);
int IsOnCyanObj(void);
int IsOnBlackObj(void);
int IsOnSuperObj(void);
int IsOnBlueFloor(void);
int IsOnDepositArea(void);
int IsOnSwampland(void);
int IsOnWhiteArea(void);
int IsOnWorld1MakerArea(void);
int IsOnTrapBlue(void);

#endif // !JUDGE_COLOR_TOOLS
