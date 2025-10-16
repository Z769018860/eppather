void func(int top, int divsum[1001], int cnt) {
    int pows[32];
    pows[0] = 1;
    pows[1] = 0;
    for (int i = 0; i <= top; i = i + 1) {
        divsum[i] = 1;
    }
    for (int p = 2; p + p <= top; p = p + 1) {
        if (divsum[p] > 1) {
            divsum[p] = divsum[p] - p;
            continue;
        }
        int x;
        for (x = 1; pows[x - 1] <= top / p; x = x + 1) {
            pows[x] = p * pows[x - 1];
        }
        int k = p - 1;
        for (int n = p + p; n <= top; n = n + p) {
            int s = 1 + pows[1];
            k = k - 1;
            if (k == 0) {
                for (int i = 2; i < x && (n % pows[i] == 0); i = i + 1) {
                    s = s + pows[i];
                }
                k = p;
            }
            divsum[n] = divsum[n] * s;
        }
    }
    for (int p = (top >> 1) + 1; p <= top; p = p + 1) {
        if (divsum[p] > 1) {
            divsum[p] = divsum[p] - p;
        }
    }
    cnt = 0;
    for (int a = 1; a <= top; a = a + 1) {
        int b = divsum[a];
        if (b > a && b <= top && divsum[b] == a) {
            cnt = cnt + 1;
        }
    }
    return;
}
