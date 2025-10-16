void fill_function(int max_x, int max_y, int data[25], int x, int y, int old_val, int new_val) {
    int neighbors_x[4];
    int neighbors_y[4];
    int stack_x[25];
    int stack_y[25];
    int stack_top[1];
    stack_top[0] = 0;
    
    if (old_val == new_val) {
        return;
    }
    
    stack_x[stack_top[0]] = x;
    stack_y[stack_top[0]] = y;
    stack_top[0] = stack_top[0] + 1;
    
    while (stack_top[0] != 0) {
        stack_top[0] = stack_top[0] - 1;
        int cur_x = stack_x[stack_top[0]];
        int cur_y = stack_y[stack_top[0]];
        
        if (data[cur_x + max_x * cur_y] == old_val) {
            data[cur_x + max_x * cur_y] = new_val;
            
            int cnt = 0;
            int points_x[4] = {cur_x, cur_x + 1, cur_x, cur_x - 1};
            int points_y[4] = {cur_y + 1, cur_y, cur_y - 1, cur_y};
            
            for (int i = 0; i < 4; i = i + 1) {
                if (points_x[i] >= 0 && points_y[i] >= 0 && points_y[i] < max_y && points_x[i] < max_x) {
                    if (data[points_x[i] + max_x * points_y[i]] == old_val) {
                        neighbors_x[cnt] = points_x[i];
                        neighbors_y[cnt] = points_y[i];
                        cnt = cnt + 1;
                    }
                }
            }
            
            for (int i = 0; i < cnt; i = i + 1) {
                stack_x[stack_top[0]] = neighbors_x[i];
                stack_y[stack_top[0]] = neighbors_y[i];
                stack_top[0] = stack_top[0] + 1;
            }
        }
    }
    return;
}
