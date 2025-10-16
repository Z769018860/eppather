int read_lines(int call_back(const char*, const char*)) {
    char buf[1024];
    char buf_end[1024];
    char begin[1024];
    char end[1024];
    char c;
    int i;
    int j;
    int k;
    int fd;
    int fs;
    
    for (i = 0; i < 1024; i = i + 1) {
        buf[i] = 0;
        buf_end[i] = 0;
        begin[i] = 0;
        end[i] = 0;
    }
    
    for (i = 0; i < 1024; i = i + 1) {
        if (buf[i] == '\r' || buf[i] == '\n') {
            if (i + 1 < 1024) {
                c = buf[i + 1];
                if ((c == '\r' || c == '\n') && c != buf[i]) {
                    i = i + 1;
                }
            }
            
            for (j = 0; j < i; j = j + 1) {
                begin[j] = buf[j];
            }
            begin[j] = '\0';
            
            for (k = 0; k < i; k = k + 1) {
                end[k] = buf[k];
            }
            end[k] = '\0';
            
            if (!call_back(begin, end)) {
                break;
            }
            
            for (j = i + 1; j < 1024; j = j + 1) {
                buf[j - i - 1] = buf[j];
            }
            i = 0;
        }
    }
    
    return 1;
}
