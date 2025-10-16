void get_nth_line(int line_no, int buf_size) {
    int buf[256];
    int curr_alloc[1];
    curr_alloc[0] = buf_size;
    int curr_ofs[1];
    curr_ofs[0] = 0;
    int line[256];
    int in_line[1];
    in_line[0] = line_no == 1;
    int bytes_read[1];
    int i[1];
    int j[1];
    
    if (line_no < 1) {
        return;
    }
    
    for (j[0] = 0; j[0] < 5; j[0] = j[0] + 1) {
        bytes_read[0] = 256;
        for (i[0] = 0; i[0] < bytes_read[0]; i[0] = i[0] + 1) {
            if (in_line[0]) {
                if (curr_ofs[0] >= curr_alloc[0]) {
                    curr_alloc[0] = curr_alloc[0] * 2;
                }
                line[curr_ofs[0]] = buf[i[0]];
                curr_ofs[0] = curr_ofs[0] + 1;
            }
            
            if (buf[i[0]] == 10) {
                line_no = line_no - 1;
                if (line_no == 1) {
                    in_line[0] = 1;
                }
                if (line_no == 0) {
                    break;
                }
            }
        }
        if (line_no == 0) {
            break;
        }
    }
    
    if (line_no != 0) {
        return;
    }
    
    line[curr_ofs[0]] = 0;
    return;
}
