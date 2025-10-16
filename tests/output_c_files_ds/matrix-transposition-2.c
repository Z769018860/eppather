void transpose(int* m, int w, int h) {
    int start;
    int next;
    int i;
    int tmp;
    
    for (start = 0; start <= w * h - 1; start = start + 1) {
        next = start;
        i = 0;
        for (;;) {
            i = i + 1;
            next = (next % h) * w + next / h;
            if (next <= start) {
                break;
            }
        }
        if (next < start || i == 1) {
            continue;
        }
        
        tmp = m[start];
        next = start;
        for (;;) {
            i = (next % h) * w + next / h;
            if (i == start) {
                m[next] = tmp;
            } else {
                m[next] = m[i];
            }
            next = i;
            if (next <= start) {
                break;
            }
        }
    }
    return;
}
