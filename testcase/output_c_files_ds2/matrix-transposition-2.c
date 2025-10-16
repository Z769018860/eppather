void transpose(int* m, int w, int h) {
    int start;
    int next;
    int i;
    int tmp[5];
    int n1;
    int n2;
    n1 = w * h;
    n2 = n1 - 1;
    
    for (start = 0; start <= n2; start = start + 1) {
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
        
        tmp[0] = m[next = start];
        for (;;) {
            i = (next % h) * w + next / h;
            if (i == start) {
                m[next] = tmp[0];
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
