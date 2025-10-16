void reader_entry(void) {
    int line_buf[4096];
    int line_len = 0;
    int line_cap = 4096;
    int count = 0;
    int c = 0;
    int eof = 0;
    int eol = 0;
    
    for (;;) {
        c = 0;
        eof = (c == -1);
        if (eof) {
            eol = (line_len > 0);
        } else {
            if (line_len == line_cap) {
                line_cap = line_cap * 2;
            }
            line_buf[line_len] = c;
            line_len = line_len + 1;
            eol = (c == '\n');
        }
        
        if (eol) {
            count = count + 1;
            line_len = 0;
        }
        
        if (eof) {
            break;
        }
    }
    
    return;
}
