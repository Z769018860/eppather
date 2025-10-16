#include <stdio.h>
#include <stdlib.h>
#include <klee/klee.h>  // KLEE 插桩头文件

#define INF 10000

// 计算曼哈顿距离作为启发式函数
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// A* 算法实现
void astar(int rows, int cols, int grid[rows][cols], int start_x, int start_y, int goal_x, int goal_y) {
    int openSet[rows][cols];
    int g[rows][cols], f[rows][cols], parentX[rows][cols], parentY[rows][cols];

    // 初始化 g 和 f 数组，设置为无穷大
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
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
        int min_f = INF;
        int current_x = -1, current_y = -1;

        // 找到 f 值最小的节点
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
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

        // 遍历相邻节点
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int neighbor_x = current_x + dx[i];
            int neighbor_y = current_y + dy[i];

            if (neighbor_x >= 0 && neighbor_x < rows && neighbor_y >= 0 && neighbor_y < cols && grid[neighbor_x][neighbor_y] == 0) {
                int tentative_g = g[current_x][current_y] + 1;

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

    // 打印路径
    printf("Path: ");
    int x = goal_x, y = goal_y;
    while (x != -1 && y != -1) {
        printf("(%d, %d) ", x, y);
        int temp_x = parentX[x][y];
        int temp_y = parentY[x][y];
        x = temp_x;
        y = temp_y;
    }
    printf("\n");
}

int main() {
    int rows, cols;

    // 使用 klee_make_symbolic 来符号化输入
    klee_make_symbolic(&rows, sizeof(rows), "rows");
    klee_make_symbolic(&cols, sizeof(cols), "cols");

    int grid[rows][cols];

    // 使用 klee_make_symbolic 进行符号化
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            klee_make_symbolic(&grid[i][j], sizeof(grid[i][j]), "grid[i][j]");
        }
    }

    int start_x, start_y, goal_x, goal_y;

    // 使用 klee_make_symbolic 来符号化起点和终点
    klee_make_symbolic(&start_x, sizeof(start_x), "start_x");
    klee_make_symbolic(&start_y, sizeof(start_y), "start_y");
    klee_make_symbolic(&goal_x, sizeof(goal_x), "goal_x");
    klee_make_symbolic(&goal_y, sizeof(goal_y), "goal_y");

    // 假设输入的坐标合理
    //klee_assume(start_x >= 0 && start_x < rows);
    //klee_assume(start_y >= 0 && start_y < cols);
    //klee_assume(goal_x >= 0 && goal_x < rows);
    //klee_assume(goal_y >= 0 && goal_y < cols);

    // 调用 A* 算法
    astar(rows, cols, grid, start_x, start_y, goal_x, goal_y);

    return 0;
}
