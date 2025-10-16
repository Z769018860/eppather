int process_lines(int arg1, int arg2, int arg3) {
    int buf[5];
    int sz[5];
    int start[5];
    int count[5];
    int lines[5];
    int dest[5];
    int src[5];
    int pos[5];
    int i;
    
    lines[0] = 1;
    dest[0] = 0;
    src[0] = 0;
    pos[0] = -1;
    
    if (arg1 != 4) {
        return;
    }
    
    count[0] = arg3;
    if (count[0] < 1) {
        return;
    }
    
    start[0] = arg2;
    if (start[0] < 1) {
        return;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        buf[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        pos[0] = pos[0] + 1;
        if (buf[pos[0]] == 10) {
            lines[0] = lines[0] + 1;
            if (lines[0] == start[0]) {
                dest[0] = pos[0] + 1;
            }
            if (lines[0] == start[0] + count[0]) {
                src[0] = pos[0] + 1;
            }
        }
    }
    
    if (start[0] + count[0] > lines[0]) {
        lines[0] = lines[0] - 1;
        return;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        buf[dest[0] + i] = buf[src[0] + i];
    }
    
    return;
}
