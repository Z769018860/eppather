void strip_init_table_strip(char str[256], int what, int init_flag) {
    int char_tbl[256];
    int i;
    for (i = 0; i < 256; i = i + 1) {
        char_tbl[i] = 0;
    }
    
    if (init_flag != 0) {
        for (i = 0; i < 32; i = i + 1) {
            char_tbl[i] = char_tbl[i] | 1;
        }
        char_tbl[127] = char_tbl[127] | 1;
        
        for (i = 65; i <= 90; i = i + 1) {
            char_tbl[i] = char_tbl[i] | 4;
            char_tbl[i + 32] = char_tbl[i + 32] | 4;
        }
        
        for (i = 128; i < 256; i = i + 1) {
            char_tbl[i] = char_tbl[i] | 2;
        }
    }
    
    int ptr_idx = 0;
    int s_idx = 0;
    while (str[s_idx] != 0) {
        if ((char_tbl[(int)str[s_idx]] & what) == 0) {
            str[ptr_idx] = str[s_idx];
            ptr_idx = ptr_idx + 1;
        }
        s_idx = s_idx + 1;
    }
    str[ptr_idx] = 0;
    return;
}
