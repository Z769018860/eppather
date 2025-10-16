void stack_operations(int init_size) {
    int stk_buf[5];
    int stk_alloc = 5;
    int stk_len = 0;
    int tmp[5];
    int i;
    int item;
    
    if (init_size == 0) {
        init_size = 4;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        stk_buf[i] = 0;
    }
    
    for (i = 97; i <= 101; i = i + 1) {
        item = i;
        if (stk_len >= stk_alloc) {
            stk_alloc = stk_alloc * 2;
        }
        stk_buf[stk_len] = item;
        stk_len = stk_len + 1;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (stk_len == 0) {
            break;
        }
        tmp[0] = stk_buf[stk_len - 1];
        stk_len = stk_len - 1;
        if (stk_len * 2 <= stk_alloc && stk_alloc >= 8) {
            stk_alloc = stk_alloc / 2;
        }
    }
    
    return;
}
