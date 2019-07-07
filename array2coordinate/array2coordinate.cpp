// Please select Shift-JIS
#include <iostream>
#include <fstream>
#include <string>

#define REP for
#define rep(i, n) REP(int i = 0; i < n; i++)

using namespace std;

int wall_num = 2;
int equations[1000][4];
int equation_num = 0;
int magnification = 10;
int map_width = 240 / magnification, map_height = 180 / magnification;
int map_data[180][240];

void addEquation(int x1, int y1, int x2, int y2)
{
    equations[equation_num][0] = x1;
    equations[equation_num][1] = y1;
    equations[equation_num][2] = x2;
    equations[equation_num][3] = y2;
    equation_num++;
}

void addEquationOfRectangle(int x1, int y1, int x2, int y2)
{
    addEquation(x1, y1, x1, y2);
    addEquation(x1, y1, x2, y1);
    addEquation(x1, y2, x2, y2);
    addEquation(x2, y1, x2, y2);
}

int main()
{
    system("chcp 932");
    system("cls");
    cout << "�ǂ̔ԍ�����͂��Ă�������" << endl;
    cout << "Please enter the number of wall" << endl;
    scanf("%d", &wall_num);

    rep(wj, map_width)
    {
        rep(hi, map_height)
        {
            scanf("%d", &map_data[hi][wj]);
        }
    }

    // �O���̕ǂ�ǉ�
    addEquationOfRectangle(0, 0, map_width * magnification, map_height * magnification);

    // ���̐��𒲂ׂ�
    rep(hi, map_height - 1)
    {
        // �����珇�Ԃ�
        rep(wj, map_width)
        {
            // �������ǂ̓A�E�g
            if (((map_data[hi][wj] == wall_num) + (map_data[hi + 1][wj] == wall_num)) == 1)
            {
                int from_x = wj;
                while (wj < map_width && ((map_data[hi][wj] == wall_num) + (map_data[hi + 1][wj] == wall_num)) == 1)
                {
                    wj++;
                }
                addEquation(from_x * magnification, (hi + 1) * magnification, wj * magnification, (hi + 1) * magnification);
            }
        }
    }

    // �c�̐��𒲂ׂ�
    rep(wi, map_width - 1)
    {
        // �����珇�Ԃ�
        rep(hj, map_height)
        {
            if (((map_data[hj][wi] == wall_num) + (map_data[hj][wi + 1] == wall_num)) == 1)
            {
                int from_y = hj;
                while (hj < map_height && ((map_data[hj][wi] == wall_num) + (map_data[hj][wi + 1] == wall_num)) == 1)
                {
                    hj++;
                }
                addEquation((wi + 1) * magnification, from_y * magnification, (wi + 1) * magnification, hj * magnification);
            }
        }
    }

    ofstream outputfile("output.txt");

    outputfile << "int equation[" << equation_num << "][4] = {" << endl;
    rep(i, equation_num)
    {
        outputfile << "{";
        rep(j, 3)
        {
            outputfile << equations[i][j] << ",";
        }
        outputfile << equations[i][3];
        if (i == equation_num - 1)
        {
            outputfile << "}" << endl;
        }
        else
        {
            outputfile << "}," << endl;
        }
        if (equations[i][0] % magnification != 0)
        {
            cout << i << "strange" << endl;
        }
    }
    outputfile << "};" << endl;
    outputfile.close();
    system("notepad output.txt");
    return 0;
}
