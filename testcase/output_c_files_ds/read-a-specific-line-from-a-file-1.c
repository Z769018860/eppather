int read_file_line() {
    int ret;
    int line_no;
    int start;
    int end;
    int ln;
    int fd;
    int s_st_size;
    int i;
    char buf[1024];
    
    ret = 1;
    start = -1;
    end = -1;
    ln = 0;
    
    if (line_no == 1) {
        start = 0;
    } else {
        if (line_no < 1) {
            return 0;
        }
    }
    
    line_no = line_no - 1;
    
    for (i = 0; i < s_st_size; i = i + 1) {
        if (ln > line_no) {
            break;
        }
        if (buf[i] != '\n') {
            continue;
        }
        ln = ln + 1;
        if (ln == line_no) {
            start = i + 1;
        } else {
            if (ln == line_no + 1) {
                end = i + 1;
            }
        }
    }
    
    if (start >= s_st_size || start < 0) {
        ret = 0;
    }
    
    return ret;
}
