int astar(int rows, int cols, int start_x, int start_y, int goal_x, int goal_y) {
    int openSet[100][100];
    int g[100][100], f[100][100], parentX[100][100], parentY[100][100];
    int grid[100][100];
    int INF = 10000;

    for (int i = 0; i < rows; i = i + 1) {
        for (int j = 0; j < cols; j = j + 1) {
            g[i][j] = INF;
            f[i][j] = INF;
            parentX[i][j] = -1;
            parentY[i][j] = -1;
            openSet[i][j] = 0;
        }
    }

    g[start_x][start_y] = 0;
    f[start_x][start_y] = abs(start_x - goal_x) + abs(start_y - goal_y);
    openSet[start_x][start_y] = 1;

    while (1) {
        int min_f = INF;
        int current_x = -1, current_y = -1;

        for (int i = 0; i < rows; i = i + 1) {
            for (int j = 0; j < cols; j = j + 1) {
                if (openSet[i][j] && f[i][j] < min_f) {
                    min_f = f[i][j];
                    current_x = i;
                    current_y = j;
                }
            }
        }

        if (current_x == -1 || (current_x == goal_x && current_y == goal_y)) {
            break;
        }

        openSet[current_x][current_y] = 0;

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i = i + 1) {
            int neighbor_x = current_x + dx[i];
            int neighbor_y = current_y + dy[i];

            if (neighbor_x >= 0 && neighbor_x < rows && neighbor_y >= 0 && neighbor_y < cols && grid[neighbor_x][neighbor_y] == 0) {
                int tentative_g = g[current_x][current_y] + 1;

                if (tentative_g < g[neighbor_x][neighbor_y]) {
                    parentX[neighbor_x][neighbor_y] = current_x;
                    parentY[neighbor_x][neighbor_y] = current_y;
                    g[neighbor_x][neighbor_y] = tentative_g;
                    f[neighbor_x][neighbor_y] = tentative_g + abs(neighbor_x - goal_x) + abs(neighbor_y - goal_y);
                    openSet[neighbor_x][neighbor_y] = 1;
                }
            }
        }
    }

    return 0;
}
