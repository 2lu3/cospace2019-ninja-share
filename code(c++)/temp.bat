int GoToDot(int x, int y)
{
  static int prev_x = -1, prev_y = -1, prev_now_dot_id = -1;

  if (PositionX == -1 && PLUSMINUS(log_x / SIZE, x, 2) && PLUSMINUS(log_y / SIZE, y, 2))
  {
    printf(" %d End GoToDot() with returning 1 because I am in PLA and it's near target(%d, %d)\n", repeated_num, x, y);
    return 1;
  }
  char map_data_to_show[MAX_DOT_NUMBER];
  for (int i = 0; i < MAX_DOT_NUMBER; i++)
  {
    if (dot[i].point <= POINT_WALL)
    {
      map_data_to_show[i] = '*';
    }
    else
    {
      map_data_to_show[i] = ' ';
    }
  }

  //If the node I want to go will be go out
  if (x < 1 || x >= DOT_WIDTH_NUMBER - 1 || y < 1 || y >= DOT_HEIGHT_NUMBER - 1)
  {
    printf("GoToDot(): (x, y) is (%d, %d) and strange\n", x, y);
  }

  if (prev_now_dot_id != now_dot_id || prev_x != x || prev_y != y)
  {
    Dijkstra(0);
  }
  prev_now_dot_id = now_dot_id;
  prev_x = x;
  prev_y = y;

  // printf("from %d %d to %d %d\n", now_dot_id - (int)(now_dot_id / DOT_WIDTH_NUMBER) * DOT_WIDTH_NUMBER, now_dot_id / DOT_WIDTH_NUMBER, x, y);

  int goal_dot = y * DOT_WIDTH_NUMBER + x;

  if (goal_dot < 0 || goal_dot >= MAX_DOT_NUMBER)
  {
    printf("strange (x,y)\n");
    return 0;
  }

  int temp = goal_dot;
  map_data_to_show[goal_dot] = 'T';
  int i = 0;

  while (dot[temp].from != now_dot_id && i < 200)
  {
    // int go_x, go_y;
    // go_y = temp / DOT_WIDTH_NUMBER;
    // go_x = temp - (int)go_y * DOT_WIDTH_NUMBER;
    temp = dot[temp].from;
    map_data_to_show[temp] = '#';
    // printf("%d\n", dot[temp].point);
    i++;
    if (temp < 0 || temp >= MAX_DOT_NUMBER)
    {
      printf(" %d GoToDot() temp = %d is srange. I will continue\n", repeated_num, temp);
      GoToPosition(x * SIZE, y * SIZE, 5, 5, 5);
      return 0;
    }
  }
  if (i == 200)
  {
    printf("\n\n\niの値が200ですByGoToNode()\n\n\n\n");
  }

  map_data_to_show[now_dot_id] = '@';

  int next_x, next_y;
  next_y = temp / DOT_WIDTH_NUMBER;
  next_x = temp - next_y * DOT_WIDTH_NUMBER;

  int now_y = now_dot_id / DOT_WIDTH_NUMBER;
  int now_x = now_dot_id - now_y * DOT_WIDTH_NUMBER;

  int distance = 20;
  if (next_x < now_x)
  {
    if (next_y < now_y)
    {
      GoToAngle(135, distance);
    }
    else if (next_y == now_y)
    {
      GoToAngle(90, distance);
    }
    else
    {
      GoToAngle(45, distance);
    }
  }
  else if (next_x == now_x)
  {
    if (next_y < now_y)
    {
      GoToAngle(180, distance);
    }
    else if (next_y == now_y)
    {
      GoToPosition(log_x - 3 + rand() % 6, log_y - 3 + rand() % 6, 6, 6, 3);
      return 1;
    }
    else
    {
      GoToAngle(0, distance);
    }
  }
  else
  {
    if (next_y < now_y)
    {
      GoToAngle(225, distance);
    }
    else if (next_y == now_y)
    {
      GoToAngle(270, distance);
    }
    else
    {
      GoToAngle(315, distance);
    }
  }
  system("cls");
  for (int i = 0; i < DOT_WIDTH_NUMBER + 2; i++)
  {
    printf("|");
  }
  printf("\n");
  for (int i = DOT_HEIGHT_NUMBER - 1; i >= 0; i--)
  {
    printf("|");
    for (int j = 0; j < DOT_WIDTH_NUMBER; j++)
    {
      int id = i * DOT_WIDTH_NUMBER + j;
      printf("%c", map_data_to_show[id]);
    }
    printf("|");
    printf("\n");
  }
  for (int i = 0; i < DOT_WIDTH_NUMBER + 2; i++)
  {
    printf("|");
  }
  printf("\n");
  return 0;
}
