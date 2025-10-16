char* get_nth_line(char* f, int line_no) {
    char buf[256];
    int curr_alloc = 256;
    int curr_ofs = 0;
    char* line = 0;
    int in_line = 0;
    int bytes_read = 256;
    int i;
    
    if (line_no < 1) {
        return 0;
    }
    
    if (line_no == 1) {
        in_line = 1;
    }
    
    for (; line_no > 0 && bytes_read > 0; ) {
        bytes_read = 0;
        for (i = 0; i < 256; i = i + 1) {
            if (bytes_read < 256) {
                buf[i] = f[bytes_read];
                bytes_read = bytes_read + 1;
            }
        }
        
        for (i = 0; i < bytes_read; i = i + 1) {
            if (in_line) {
                if (curr_ofs >= curr_alloc) {
                    curr_alloc = curr_alloc * 2;
                    char* new_line = 0;
                    for (int j = 0; j < curr_ofs; j = j + 1) {
                        new_line[j] = line[j];
                    }
                    line = new_line;
                }
                line[curr_ofs] = buf[i];
                curr_ofs = curr_ofs + 1;
            }
            
            if (buf[i] == '\n') {
                line_no = line_no - 1;
                if (line_no == 1) {
                    in_line = 1;
                }
                if (line_no == 0) {
                    break;
                }
            }
        }
    }
    
    if (line_no != 0) {
        return 0;
    }
    
    line[curr_ofs] = '\0';
    return line;
}
