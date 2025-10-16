void reader_entry(int input, int co_active, int co_create, int co_delete, int co_switch) {
    int line_buf[5];
    int line_len[5];
    int line_cap[5];
    int count[5];
    int reader[5];
    int printer[5];
    int newcap[5];
    int c[5];
    int eof[5];
    int eol[5];
    int newbuf[5];
    int i;
    
    line_cap[0] = 4096;
    line_len[0] = 0;
    count[0] = 0;
    
    for (i = 0; i < 5; i = i + 1) {
        c[0] = input;
        eof[0] = (c[0] == (-1));
        if (eof[0]) {
            eol[0] = (line_len[0] > 0);
        } else {
            if (line_len[0] == line_cap[0]) {
                newcap[0] = line_cap[0] * 2;
                line_cap[0] = newcap[0];
            }
            line_buf[line_len[0]] = c[0];
            line_len[0] = line_len[0] + 1;
            eol[0] = (c[0] == 10);
        }
        
        if (eol[0]) {
            co_switch = printer[0];
            line_len[0] = 0;
        }
    }
    
    line_buf[0] = 0;
    co_switch = printer[0];
    return;
}
