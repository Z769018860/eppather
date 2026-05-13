int stack_func(int x) {
    int s_bottom[5];
    int s_top[5];
    int s_allocated_top[5];
    int qtty[5];
    int new_qtty[5];
    int new_size[5];
    int MINIMUM_SIZE[5];
    MINIMUM_SIZE[0] = 1;
    int GROWTH_FACTOR[5];
    GROWTH_FACTOR[0] = 2;
    
    s_bottom[0] = 0;
    s_top[0] = s_bottom[0] - 1;
    s_allocated_top[0] = s_bottom[0] + MINIMUM_SIZE[0] - 1;
    
    if (s_top[0] < s_bottom[0]) {
        return 1;
    } else {
        return 0;
    }
    
    if (s_top[0] == s_allocated_top[0]) {
        qtty[0] = s_top[0] - s_bottom[0] + 1;
        new_qtty[0] = GROWTH_FACTOR[0] * qtty[0];
        s_top[0] = s_bottom[0] + qtty[0] - 1;
        s_allocated_top[0] = s_bottom[0] + new_qtty[0] - 1;
    }
    s_top[0] = s_top[0] + 1;
    s_top[0] = x;
    
    s_top[0] = s_top[0] - 1;
    int temp[5];
    temp[0] = s_top[0];
    
    if (s_top[0] == s_allocated_top[0]) {
        return;
    }
    qtty[0] = s_top[0] - s_bottom[0] + 1;
    if (qtty[0] < MINIMUM_SIZE[0]) {
        qtty[0] = MINIMUM_SIZE[0];
    }
    new_size[0] = qtty[0];
    s_allocated_top[0] = s_bottom[0] + qtty[0] - 1;
    
    return;
}
