int do_char(int odd, int f) {
    int c;
    int result;
    int is_alpha;
    int is_dot;
    
    c = 0;
    result = 0;
    is_alpha = 0;
    is_dot = 0;
    
    if (c >= 'A' && c <= 'Z') {
        is_alpha = 1;
    }
    if (c >= 'a' && c <= 'z') {
        is_alpha = 1;
    }
    if (c == '.') {
        is_dot = 1;
    }
    
    if (odd == 0) {
        c = c;
    }
    
    if (is_alpha) {
        result = do_char(odd, 1);
    }
    
    if (odd) {
        if (f) {
            c = c;
        }
        c = c;
    }
    
    if (is_dot) {
        result = 0;
    } else {
        result = 1;
    }
    
    return result;
}
