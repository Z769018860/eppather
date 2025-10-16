void flood_fill(int data[25], int max_x, int max_y, int x, int y, int old_val, int new_val) {
    if (old_val == new_val) {
        return;
    }
    
    int stack_x[100];
    int stack_y[100];
    int top = 0;
    
    stack_x[top] = x;
    stack_y[top] = y;
    top = top + 1;
    
    while (top > 0) {
        top = top - 1;
        int cur_x = stack_x[top];
        int cur_y = stack_y[top];
        
        if (data[cur_x + max_x * cur_y] == old_val) {
            data[cur_x + max_x * cur_y] = new_val;
            
            int neighbors_x[4];
            int neighbors_y[4];
            int cnt = 0;
            
            if (cur_y + 1 < max_y && data[cur_x + max_x * (cur_y + 1)] == old_val) {
                neighbors_x[cnt] = cur_x;
                neighbors_y[cnt] = cur_y + 1;
                cnt = cnt + 1;
            }
            if (cur_x + 1 < max_x && data[cur_x + 1 + max_x * cur_y] == old_val) {
                neighbors_x[cnt] = cur_x + 1;
                neighbors_y[cnt] = cur_y;
                cnt = cnt + 1;
            }
            if (cur_y - 1 >= 0 && data[cur_x + max_x * (cur_y - 1)] == old_val) {
                neighbors_x[cnt] = cur_x;
                neighbors_y[cnt] = cur_y - 1;
                cnt = cnt + 1;
            }
            if (cur_x - 1 >= 0 && data[cur_x - 1 + max_x * cur_y] == old_val) {
                neighbors_x[cnt] = cur_x - 1;
                neighbors_y[cnt] = cur_y;
                cnt = cnt + 1;
            }
            
            for (int i = 0; i < cnt; i = i + 1) {
                stack_x[top] = neighbors_x[i];
                stack_y[top] = neighbors_y[i];
                top = top + 1;
            }
        }
    }
    return;
}
