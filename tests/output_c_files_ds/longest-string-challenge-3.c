int process_lines(int a, int b, int c) {
    int x;
    int y;
    int z;
    int tmp[2];
    int len;
    int l1;
    int l2;
    int line[1];
    int buf[1];
    int longest[1];
    
    line[0] = 0;
    buf[0] = 0;
    longest[0] = 0;
    
    for (;;) {
        len = 0;
        line[0] = 0;
        for (;;) {
            x = a;
            if (x == -1) {
                break;
            }
            tmp[0] = x;
            len = len + 1;
            for (y = 0; y < len; y = y + 1) {
                line[y] = tmp[0];
            }
            if (tmp[0] == '\n') {
                break;
            }
        }
        if (tmp[0] != '\n') {
            tmp[0] = '\n';
            for (y = 0; y < len; y = y + 1) {
                line[y] = tmp[0];
            }
        }
        
        l1 = 0;
        for (x = 0; line[x] != 0; x = x + 1) {
            l1 = l1 + 1;
        }
        if (l1 == 0) {
            break;
        }
        
        l2 = 0;
        for (x = 0; longest[x] != 0; x = x + 1) {
            l2 = l2 + 1;
        }
        
        if (l1 > l2) {
            buf[0] = 0;
            longest[0] = 0;
            for (x = 0; line[x] != 0; x = x + 1) {
                longest[x] = line[x];
            }
        } else {
            if (l2 > l1) {
                continue;
            }
        }
        
        for (x = 0; line[x] != 0; x = x + 1) {
            buf[x] = line[x];
        }
    }
    
    return;
}
