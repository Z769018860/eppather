int percolate(int grid[15][15]) {
    int startR = 0;
    int bottom = 14;
    int c;
    for (c = 0; c < 15; c = c + 1) {
        if (grid[startR][c] == 32) {
            int r = startR;
            int stack_r[225];
            int stack_c[225];
            int top = 0;
            stack_r[top] = r;
            stack_c[top] = c;
            top = top + 1;
            grid[r][c] = 46;
            while (top > 0) {
                top = top - 1;
                r = stack_r[top];
                c = stack_c[top];
                if (r == bottom) {
                    return 1;
                }
                if (r < bottom && grid[r + 1][c] == 32) {
                    grid[r + 1][c] = 46;
                    stack_r[top] = r + 1;
                    stack_c[top] = c;
                    top = top + 1;
                }
                if (c > 0 && grid[r][c - 1] == 32) {
                    grid[r][c - 1] = 46;
                    stack_r[top] = r;
                    stack_c[top] = c - 1;
                    top = top + 1;
                }
                if (c < 14 && grid[r][c + 1] == 32) {
                    grid[r][c + 1] = 46;
                    stack_r[top] = r;
                    stack_c[top] = c + 1;
                    top = top + 1;
                }
                if (r > 0 && grid[r - 1][c] == 32) {
                    grid[r - 1][c] = 46;
                    stack_r[top] = r - 1;
                    stack_c[top] = c;
                    top = top + 1;
                }
            }
        }
    }
    return 0;
}
