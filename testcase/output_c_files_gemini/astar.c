void astar(int grid[10][10], int start_x, int start_y, int goal_x, int goal_y)
{
    int openSet[10][10];
    int g[10][10];
    int f[10][10];
    int parentX[10][10];
    int parentY[10][10];
    int i;
    int j;

    for (i = 0; i < 10; i = i + 1)
    {
        for (j = 0; j < 10; j = j + 1)
        {
            g[i][j] = 10000;
            f[i][j] = 10000;
            parentX[i][j] = -1;
            parentY[i][j] = -1;
            openSet[i][j] = 0;
        }
    }

    g[start_x][start_y] = 0;

    int dx_h_start;
    int dy_h_start;
    int abs_dx_h_start;
    int abs_dy_h_start;
    dx_h_start = start_x - goal_x;
    dy_h_start = start_y - goal_y;
    if (dx_h_start > 0)
    {
        abs_dx_h_start = dx_h_start;
    }
    else
    {
        abs_dx_h_start = 0 - dx_h_start;
    }
    if (dy_h_start > 0)
    {
        abs_dy_h_start = dy_h_start;
    }
    else
    {
        abs_dy_h_start = 0 - dy_h_start;
    }
    f[start_x][start_y] = abs_dx_h_start + abs_dy_h_start;
    openSet[start_x][start_y] = 1;

    int loop_count;
    for (loop_count = 0; loop_count < 100; loop_count = loop_count + 1)
    {
        int min_f = 10000;
        int current_x = -1;
        int current_y = -1;

        for (i = 0; i < 10; i = i + 1)
        {
            for (j = 0; j < 10; j = j + 1)
            {
                if (openSet[i][j] != 0 && f[i][j] < min_f)
                {
                    min_f = f[i][j];
                    current_x = i;
                    current_y = j;
                }
            }
        }

        if (current_x == -1)
        {
            break;
        }
        if (current_x == goal_x && current_y == goal_y)
        {
            break;
        }

        openSet[current_x][current_y] = 0;

        int dx[4];
        int dy[4];
        dx[0] = -1;
        dx[1] = 1;
        dx[2] = 0;
        dx[3] = 0;
        dy[0] = 0;
        dy[1] = 0;
        dy[2] = -1;
        dy[3] = 1;

        int k;
        for (k = 0; k < 4; k = k + 1)
        {
            int neighbor_x = current_x + dx[k];
            int neighbor_y = current_y + dy[k];

            if (neighbor_x >= 0 && neighbor_x < 10 && neighbor_y >= 0 && neighbor_y < 10)
            {
                if (grid[neighbor_x][neighbor_y] == 0)
                {
                    int tentative_g = g[current_x][current_y] + 1;
                    if (tentative_g < g[neighbor_x][neighbor_y])
                    {
                        parentX[neighbor_x][neighbor_y] = current_x;
                        parentY[neighbor_x][neighbor_y] = current_y;
                        g[neighbor_x][neighbor_y] = tentative_g;

                        int h_val_neighbor;
                        int dx_h_n = neighbor_x - goal_x;
                        int dy_h_n = neighbor_y - goal_y;
                        int abs_dx_h_n;
                        int abs_dy_h_n;
                        if (dx_h_n > 0)
                        {
                            abs_dx_h_n = dx_h_n;
                        }
                        else
                        {
                            abs_dx_h_n = 0 - dx_h_n;
                        }
                        if (dy_h_n > 0)
                        {
                            abs_dy_h_n = dy_h_n;
                        }
                        else
                        {
                            abs_dy_h_n = 0 - dy_h_n;
                        }
                        h_val_neighbor = abs_dx_h_n + abs_dy_h_n;
                        f[neighbor_x][neighbor_y] = tentative_g + h_val_neighbor;
                        openSet[neighbor_x][neighbor_y] = 1;
                    }
                }
            }
        }
    }
    return;
}
