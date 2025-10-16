int solve(int hh, int ww, int recur) {
    int grid[10000];
    int next[4];
    int dir[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    int w = ww;
    int h = hh;
    int len;
    unsigned long long cnt = 0;
    int t;
    int cx;
    int cy;
    int x;
    int i;
    int y;
    
    if ((h & 1) != 0) {
        t = w;
        w = h;
        h = t;
    }
    if ((h & 1) != 0) {
        return 0;
    }
    if (w == 1) {
        return 1;
    }
    if (w == 2) {
        return h;
    }
    if (h == 2) {
        return w;
    }
    
    cy = h / 2;
    cx = w / 2;
    len = (h + 1) * (w + 1);
    
    for (i = 0; i < len; i = i + 1) {
        grid[i] = 0;
    }
    len = len - 1;
    
    next[0] = -1;
    next[1] = -w - 1;
    next[2] = 1;
    next[3] = w + 1;
    
    if (recur != 0) {
        cnt = 0;
    }
    for (x = cx + 1; x < w; x = x + 1) {
        t = cy * (w + 1) + x;
        grid[t] = 1;
        grid[len - t] = 1;
        
        int stack_y[1000];
        int stack_x[1000];
        int stack_i[1000];
        int stack_t[1000];
        int stack_ptr = 0;
        
        stack_y[stack_ptr] = cy - 1;
        stack_x[stack_ptr] = x;
        stack_i[stack_ptr] = 0;
        stack_ptr = stack_ptr + 1;
        
        while (stack_ptr > 0) {
            stack_ptr = stack_ptr - 1;
            y = stack_y[stack_ptr];
            x = stack_x[stack_ptr];
            i = stack_i[stack_ptr];
            
            if (y == 0 || y == h || x == 0 || x == w) {
                cnt = cnt + 2;
                continue;
            }
            
            t = y * (w + 1) + x;
            grid[t] = grid[t] + 1;
            grid[len - t] = grid[len - t] + 1;
            
            for (; i < 4; i = i + 1) {
                if (grid[t + next[i]] == 0) {
                    stack_y[stack_ptr] = y;
                    stack_x[stack_ptr] = x;
                    stack_i[stack_ptr] = i + 1;
                    stack_ptr = stack_ptr + 1;
                    
                    stack_y[stack_ptr] = y + dir[i][0];
                    stack_x[stack_ptr] = x + dir[i][1];
                    stack_i[stack_ptr] = 0;
                    stack_ptr = stack_ptr + 1;
                    break;
                }
            }
            
            if (i == 4) {
                grid[t] = grid[t] - 1;
                grid[len - t] = grid[len - t] - 1;
            }
        }
    }
    cnt = cnt + 1;
    
    if (h == w) {
        cnt = cnt * 2;
    } else if ((w & 1) == 0 && recur != 0) {
        int temp = solve(w, h, 0);
        cnt = cnt + temp;
    }
    
    return cnt;
}
