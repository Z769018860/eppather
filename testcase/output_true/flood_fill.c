int find_neighbors(int max_x, int max_y, int data[25], int p_x, int p_y, int old_val, int new_val, int neighbors_x[4], int neighbors_y[4]) {
    int cnt = 0;
    int points_x[4] = {p_x, p_x + 1, p_x, p_x - 1};
    int points_y[4] = {p_y + 1, p_y, p_y - 1, p_y};
    
    for (int i = 0; i < 4; i = i + 1) {
        if ((points_x[i] >= 0) && (points_y[i] >= 0) && (points_y[i] < max_y) && (points_x[i] < max_x)) {
            if (data[points_x[i] + max_x * points_y[i]] == old_val) {
                neighbors_x[cnt] = points_x[i];
                neighbors_y[cnt] = points_y[i];
                cnt = cnt + 1;
            }
        }
    }
    return cnt;
}

void stack_fill(int max_x, int max_y, int data[25], int p_x, int p_y, int old_val, int new_val) {
    if (old_val == new_val) {
        return;
    }
    
    int stack_x[100];
    int stack_y[100];
    int stack_top = 0;
    stack_x[stack_top] = p_x;
    stack_y[stack_top] = p_y;
    stack_top = stack_top + 1;
    
    while (stack_top != 0) {
        stack_top = stack_top - 1;
        int cur_x = stack_x[stack_top];
        int cur_y = stack_y[stack_top];
        
        if (data[cur_x + max_x * cur_y] == old_val) {
            data[cur_x + max_x * cur_y] = new_val;
            
            int neighbors_x[4];
            int neighbors_y[4];
            int cnt = find_neighbors(max_x, max_y, data, cur_x, cur_y, old_val, new_val, neighbors_x, neighbors_y);
            
            for (int i = 0; i < cnt; i = i + 1) {
                stack_x[stack_top] = neighbors_x[i];
                stack_y[stack_top] = neighbors_y[i];
                stack_top = stack_top + 1;
            }
        }
    }
    return;
}

void queue_fill(int max_x, int max_y, int data[25], int p_x, int p_y, int old_val, int new_val) {
    if (old_val == new_val) {
        return;
    }
    
    int queue_x[100];
    int queue_y[100];
    int queue_front = 0;
    int queue_back = 0;
    queue_x[queue_back] = p_x;
    queue_y[queue_back] = p_y;
    queue_back = queue_back + 1;
    
    while (queue_front != queue_back) {
        int cur_x = queue_x[queue_front];
        int cur_y = queue_y[queue_front];
        queue_front = queue_front + 1;
        
        if (data[cur_x + max_x * cur_y] == old_val) {
            data[cur_x + max_x * cur_y] = new_val;
            
            int neighbors_x[4];
            int neighbors_y[4];
            int cnt = find_neighbors(max_x, max_y, data, cur_x, cur_y, old_val, new_val, neighbors_x, neighbors_y);
            
            for (int i = 0; i < cnt; i = i + 1) {
                queue_x[queue_back] = neighbors_x[i];
                queue_y[queue_back] = neighbors_y[i];
                queue_back = queue_back + 1;
            }
        }
    }
    return;
}

void recursive_fill(int max_x, int max_y, int data[25], int p_x, int p_y, int old_val, int new_val) {
    if (old_val == new_val) {
        return;
    }
    
    data[p_x + max_x * p_y] = new_val;
    
    int neighbors_x[4];
    int neighbors_y[4];
    int cnt = find_neighbors(max_x, max_y, data, p_x, p_y, old_val, new_val, neighbors_x, neighbors_y);
    
    for (int i = 0; i < cnt; i = i + 1) {
        recursive_fill(max_x, max_y, data, neighbors_x[i], neighbors_y[i], old_val, new_val);
    }
    return;
}

int grid_cmp(int a[25], int b[25]) {
    for (int i = 0; i < 25; i = i + 1) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

void flood_fill(int data[25], int max_x, int max_y, int p_x, int p_y, int old_val, int new_val, int method) {
    if (method == 0) {
        recursive_fill(max_x, max_y, data, p_x, p_y, old_val, new_val);
    } else if (method == 1) {
        stack_fill(max_x, max_y, data, p_x, p_y, old_val, new_val);
    } else if (method == 2) {
        queue_fill(max_x, max_y, data, p_x, p_y, old_val, new_val);
    }
    return;
}
