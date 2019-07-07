#include "JudgeColorTools.h"

void InputColorInformation(void);

int red_obj[3][2] = {{232, 255}, {29, 39}, {29, 39}};
int cyan_obj[3][2] = {{29, 39}, {249, 255}, {255, 255}};
int black_obj[3][2] = {{29, 39}, {29, 39}, {29, 39}};
int trap_line[3][2] = {{204, 235}, {217, 248}, {0, 0}};
int blue_zone[3][2] = {{0, 0}, {150, 171}, {255, 255}};
int object_box[3][2] = {{235, 204}, {148, 130}, {0, 0}};
int gray_zone[3][2] = {{130, 160}, {140, 165}, {185, 210}};
int sp_obj[3][2] = {{255, 232}, {41, 60}, {255, 255}};
int purple_line[3][2] = {{150, 180}, {80, 100}, {180, 220}};
int trap_blue[3][2] = {{89, 102}, {41, 47}, {180, 199}};

int ColorJudgeLeft(int col[3][2])
{
  return col[0][0] <= CSLeft_R && CSLeft_R <= col[0][1] && col[1][0] <= CSLeft_G && CSLeft_G <= col[1][1] && col[2][0] <= CSLeft_B && CSLeft_B <= col[2][1];
}
int ColorJudgeRight(int col[3][2])
{
  return col[0][0] <= CSRight_R && CSRight_R <= col[0][1] && col[1][0] <= CSRight_G && CSRight_G <= col[1][1] && col[2][0] <= CSRight_B && CSRight_B <= col[2][1];
}
int EitherColorJudge(int col[3][2])
{
  return ColorJudgeLeft(col) || ColorJudgeRight(col);
}
int BothColorJudge(int col[3][2])
{
  return ColorJudgeLeft(col) && ColorJudgeRight(col);
}

void judgeColorToolsSetup(void)
{
  InputColorInformation();
}

#define COLOR_TYPE_NUMBER 9
#define COLOR_YELLOW 0
#define COLOR_RED 1
#define COLOR_CYAN 2
#define COLOR_BLACK 3
#define COLOR_SUPER_OBJ 4
#define COLOR_BLUE_FLOOR 5
#define COLOR_DEPOSIT 6
#define COLOR_SWAMPLAND 7
#define COLOR_TRAP_BLUE 8
int color_world2[COLOR_TYPE_NUMBER][6];
int ColorInformationInputer(int num, int col[3][2])
{
  logMessageOption("ColorInformationInputer() : Input new color", MODE_VERBOSE);
  if (num >= COLOR_TYPE_NUMBER)
  {
    errorMessageOption("ColorInformationInputer(): num's value is strange\n", MODE_NORMAL);
    return ERROR;
  }
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      if (col[i][j] < 0 || col[i][j] > 255)
      {
        errorMessageOption("ColorInformationInputer() : 色の値が異常です", MODE_NORMAL);
      }
      color_world2[num][j * 3 + i] = col[i][j];
    }
  }
  logMessageOption("ColorInformationInputer() successful\n", MODE_VERBOSE);
  return 1;
}
void InputColorInformation(void)
{
  logMessageOption("Start InputColorInformation()\n", MODE_VERBOSE);
  ColorInformationInputer(COLOR_YELLOW, trap_line);
  ColorInformationInputer(COLOR_RED, red_obj);
  ColorInformationInputer(COLOR_CYAN, cyan_obj);
  ColorInformationInputer(COLOR_BLACK, black_obj);
  ColorInformationInputer(COLOR_SUPER_OBJ, sp_obj);
  ColorInformationInputer(COLOR_BLUE_FLOOR, blue_zone);
  ColorInformationInputer(COLOR_DEPOSIT, object_box);
  ColorInformationInputer(COLOR_SWAMPLAND, gray_zone);
  ColorInformationInputer(COLOR_TRAP_BLUE, trap_blue);
  logMessageOption("End InputColorInformation\n", MODE_VERBOSE);
}

int IsOnStuff(int num)
{
  int ans = 0;
  int color_width = 10;
  if (num == COLOR_SUPER_OBJ)
  {
    color_width += 20;
  }
  if ((color_world2[num][0] + color_width > CSLeft_R && color_world2[num][0] - color_width < CSLeft_R && color_world2[num][1] + color_width > CSLeft_G && color_world2[num][1] - color_width < CSLeft_G && color_world2[num][2] + color_width > CSLeft_B && color_world2[num][2] - color_width < CSLeft_B) || (color_world2[num][3] + color_width > CSLeft_R && color_world2[num][3] - color_width < CSLeft_R && color_world2[num][4] + color_width > CSLeft_G && color_world2[num][4] - color_width < CSLeft_G && color_world2[num][5] + color_width > CSLeft_B && color_world2[num][5] - color_width < CSLeft_B))
  {
    ans++;
  }
  if ((color_world2[num][0] + color_width > CSRight_R && color_world2[num][0] - color_width < CSRight_R && color_world2[num][1] + color_width > CSRight_G && color_world2[num][1] - color_width < CSRight_G && color_world2[num][2] + color_width > CSRight_B && color_world2[num][2] - color_width < CSRight_B) || (color_world2[num][3] + color_width > CSRight_R && color_world2[num][3] - color_width < CSRight_R && color_world2[num][4] + color_width > CSRight_G && color_world2[num][4] - color_width < CSRight_G && color_world2[num][5] + color_width > CSRight_B && color_world2[num][5] - color_width < CSRight_B))
  {
    ans += 2;
  }
  return ans;
}
int IsOnYellowLine(void)
{
  return IsOnStuff(COLOR_YELLOW);
}
int IsOnRedObj(void)
{
  return IsOnStuff(COLOR_RED);
}
int IsOnCyanObj(void)
{
  return IsOnStuff(COLOR_CYAN);
}
int IsOnBlackObj(void)
{
  return IsOnStuff(COLOR_BLACK);
}
int IsOnSuperObj(void)
{
  return IsOnStuff(COLOR_SUPER_OBJ);
}
int IsOnBlueFloor(void)
{
  return IsOnStuff(COLOR_BLUE_FLOOR);
}
int IsOnDepositArea(void)
{
  return IsOnStuff(COLOR_DEPOSIT);
}
int IsOnSwampland(void)
{
  return IsOnStuff(COLOR_SWAMPLAND);
}
int IsOnTrapBlue(void)
{
  return IsOnStuff(COLOR_TRAP_BLUE);
}
