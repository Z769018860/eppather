#define INF 10000

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void astar(int rows, int cols, int grid[5][5], int start_x, int start_y, int goal_x, int goal_y) {
    int openSet[5][5] = {0};
    int g[5][5], f[5][5], parentX[5][5], parentY[5][5];
    int i, j;
    int min_f, current_x, current_y;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int neighbor_x, neighbor_y, tentative_g;
    int x, y;

    for (i = 0; i < rows; i = i + 1) {
        for (j = 0; j < cols; j = j + 1) {
            g[i][j] = INF;
            f[i][j] = INF;
            parentX[i][j] = -1;
            parentY[i][j] = -1;
            openSet[i][j] = 0;
        }
    }

    g[start_x][start_y] = 0;
    f[start_x][start_y] = heuristic(start_x, start_y, goal_x, goal_y);
    openSet[start_x][start_y] = 1;

    while (1) {
        min_f = INF;
        current_x = -1;
        current_y = -1;

        for (i = 0; i < rows; i = i + 1) {
            for (j = 0; j < cols; j = j + 1) {
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

        for (i = 0; i < 4; i = i + 1) {
            neighbor_x = current_x + dx[i];
            neighbor_y = current_y + dy[i];

            if (neighbor_x >= 0 && neighbor_x < rows && neighbor_y >= 0 && neighbor_y < cols && grid[neighbor_x][neighbor_y] == 0) {
                tentative_g = g[current_x][current_y] + 1;

                if (tentative_g < g[neighbor_x][neighbor_y]) {
                    parentX[neighbor_x][neighbor_y] = current_x;
                    parentY[neighbor_x][neighbor_y] = current_y;
                    g[neighbor_x][neighbor_y] = tentative_g;
                    f[neighbor_x][neighbor_y] = tentative_g + heuristic(neighbor_x, neighbor_y, goal_x, goal_y);
                    openSet[neighbor_x][neighbor_y] = 1;
                }
            }
        }
    }

    x = goal_x;
    y = goal_y;
    while (x != -1 && y != -1) {
        x = parentX[x][y];
        y = parentY[x][y];
    }
    return;
}
