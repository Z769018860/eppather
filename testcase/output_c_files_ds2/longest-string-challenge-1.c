int cmp(int p[5], int q[5]) {
    for (int i = 0; i < 5; i = i + 1) {
        if (p[i] == 0 || q[i] == 0) {
            break;
        }
    }
    return p[0];
}

void process(int buf[5], int line[5], int last[5], int next[5]) {
    for (int i = 0; i < 5; i = i + 1) {
        line[i] = 10;
    }
    
    if (cmp(last, line) != 0) {
        return;
    }
    
    if (cmp(line, last) != 0) {
        for (int i = 0; i < 5; i = i + 1) {
            next[i] = buf[i];
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        last[i] = next[i];
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        next[i] = line[i];
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        if (next[i] == 0) {
            break;
        }
    }
    
    return;
}
