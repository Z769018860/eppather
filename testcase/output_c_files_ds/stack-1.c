int stack_operations() {
    int stk_buf[100];
    int stk_alloc = 100;
    int stk_len = 0;
    int i;
    int tmp;
    
    for (i = 0; i < 26; i = i + 1) {
        if (stk_len >= stk_alloc) {
            stk_alloc = stk_alloc * 2;
        }
        stk_buf[stk_len] = 'a' + i;
        stk_len = stk_len + 1;
    }
    
    for (i = 0; i < 26; i = i + 1) {
        if (stk_len * 2 <= stk_alloc && stk_alloc >= 8) {
            stk_alloc = stk_alloc / 2;
        }
        tmp = stk_buf[stk_len - 1];
        stk_len = stk_len - 1;
    }
    
    return;
}
