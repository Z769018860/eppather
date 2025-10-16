int read_lines(int (*call_back)(const char*, const char*), int fs_st_size) {
    int fd[5];
    fd[0] = 0;
    char buf[5];
    char buf_end[5];
    char begin[5];
    char end[5];
    char c[5];
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        buf[i] = 0;
        buf_end[i] = 0;
        begin[i] = 0;
        end[i] = 0;
        c[i] = 0;
    }
    
    buf_end[0] = buf[0] + fs_st_size;
    begin[0] = buf[0];
    end[0] = buf[0];
    
    for (i = 0; i < 5; i = i + 1) {
        if (! (end[0] == 13 || end[0] == 10)) {
            end[0] = end[0] + 1;
            if (end[0] < buf_end[0]) {
                continue;
            }
        } else {
            if (1 + end[0] < buf_end[0]) {
                c[0] = *(1 + end);
                if ((c[0] == 13 || c[0] == 10) && c[0] != end[0]) {
                    end[0] = end[0] + 1;
                }
            }
        }
        
        if (! call_back(begin, end)) {
            break;
        }
        
        begin[0] = end[0] + 1;
        end[0] = end[0] + 1;
        if (begin[0] >= buf_end[0]) {
            break;
        }
    }
    
    return 1;
}

int print_line(const char* begin, const char* end) {
    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (begin[i] == 0 || end[i] == 0) {
            break;
        }
    }
    return 1;
}
