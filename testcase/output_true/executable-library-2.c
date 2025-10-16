int hailstone(int n, int seq[5]) {
    int len = 0;
    int buf_len = 4;
    int n1 = 1;
    int n2 = 2;
    int n3 = 3;
    int n4 = 4;
    int n5 = 5;
    
    for (int i = 0; i < 5; i = i + 1) {
        if (len >= buf_len) {
            buf_len = buf_len * 2;
        }
        if (seq) {
            seq[len] = n;
        }
        len = len + 1;
        if (n == n1) {
            break;
        }
        if (n & n1) {
            n = n3 * n + n1;
        } else {
            n = n >> n1;
        }
    }
    return len;
}
