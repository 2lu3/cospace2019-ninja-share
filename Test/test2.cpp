#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <chrono>
#include <random>
#include <cstdlib>
#include <iomanip>

#define N 10
#define ABS(i) ((i ^ (i >> 31)) - (i >> 31))
#define REP for
#define rep(i, n) REP(long i = 0; i < n; i++)

using namespace std;

class ProcessingTime
{
public:
  void start(void)
  {
    start_time = chrono::system_clock::now();
  }
  double end(void)
  {
    end_time = chrono::system_clock::now();
    double elapsed = (double)chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    return elapsed;
  }

private:
  chrono::system_clock::time_point start_time, end_time;
};

ProcessingTime Processing_time;

int us_data[N][5] = {
    {47, 347, 6, 8, 16},
    {42, 7, 11, 20, 15},
    {44, 17, 10, 24, 11},
    {44, 351, 9, 12, 18},
    {29, 20, 15, 38, 16},
    {30, 9, 24, 42, 29},
    {44, 348, 9, 12, 20},
    {45, 2, 9, 15, 13},
    {40, 1, 13, 21, 19},
    {43, 19, 12, 30, 12}};
int angle[3] = {0, 45, -45};
//  a, b, c
double us_distance[3] = {8, 13, 4};

int is_test = 0;

int main()
{
  cout << std::fixed;
  // 前処理
  rep(i, N)
  {
    us_data[i][1] += 90;
    us_data[i][1] %= 360;
  }

  double k = 0.6;
  int epoch_num = 1000;
  double difference_sum = 0;
  rep(epoch, epoch_num)
  {
    k *= 1 - epoch / epoch_num;
    difference_sum = 0;
    rep(i, N)
    {
      double y = sin(static_cast<double>(us_data[i][1]) * M_PI / 180) * us_distance[2];
      rep(j, 3)
      {
        double wall_y = sin(static_cast<double>(us_data[i][1] + angle[j]) * M_PI / 180) * us_distance[j % 2];

        double difference = static_cast<double>(us_data[i][0]) + y + wall_y - 50;
        if (is_test)
        {
          cout << y + wall_y + us_data[i][0] << " " << difference << endl;
        }
        else
        {
          difference_sum += fabs(difference);
          // cout << static_cast<double>(us_data[i][0]) + y + wall_y << " " << difference << endl;
          // us_distance[2] -= difference * y / (y + wall_y) * k;
          us_distance[j % 2] -= difference * wall_y / (y + wall_y) * k;
          // cout << difference * y / (y + wall_y) * k << endl;
        }
      }
    }
    if (is_test)
    {
      return 1;
    }
    cout << "difference " << difference_sum / N / 3 << endl;
  }
  rep(i, 3)
  {
    cout << us_distance[i] << " ";
  }
  cout << endl;
  cout << "all finished" << endl;
}
