int check_reg_dir(const char* path, int is_dir) {
    int result;
    int mode;
    int st_mode;
    int i;
    int sb[13];
    
    result = 0;
    mode = 0;
    st_mode = 0;
    
    for (i = 0; i < 13; i = i + 1) {
        sb[i] = 0;
    }
    
    if (path[0] == '/') {
        if (path[1] == 'i' && path[2] == 'n' && path[3] == 'p' && path[4] == 'u' && path[5] == 't' && path[6] == '.' && path[7] == 't' && path[8] == 'x' && path[9] == 't' && path[10] == '\0') {
            st_mode = 32768;
        }
        if (path[1] == 'd' && path[2] == 'o' && path[3] == 'c' && path[4] == 's' && path[5] == '\0') {
            st_mode = 16384;
        }
    } else {
        if (path[0] == 'i' && path[1] == 'n' && path[2] == 'p' && path[3] == 'u' && path[4] == 't' && path[5] == '.' && path[6] == 't' && path[7] == 'x' && path[8] == 't' && path[9] == '\0') {
            st_mode = 32768;
        }
        if (path[0] == 'd' && path[1] == 'o' && path[2] == 'c' && path[3] == 's' && path[4] == '\0') {
            st_mode = 16384;
        }
    }
    
    if (is_dir) {
        mode = 16384;
    } else {
        mode = 32768;
    }
    
    if (st_mode == mode) {
        result = 1;
    }
    
    return result;
}
