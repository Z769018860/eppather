int entropy_combined(char S[100], int len) {
    int wherechar[256];
    int hist[100];
    int histlen;
    int i;
    int j;
    int H_num[5];
    int H_den[5];
    int H[5];
    int n;
    int temp;
    
    histlen = 0;
    for (i = 0; i < 256; i = i + 1) {
        wherechar[i] = -1;
    }
    for (i = 0; i < 100; i = i + 1) {
        hist[i] = 0;
    }
    for (i = 0; i < len; i = i + 1) {
        if (wherechar[(int)S[i]] == -1) {
            wherechar[(int)S[i]] = histlen;
            histlen = histlen + 1;
        }
        hist[wherechar[(int)S[i]]] = hist[wherechar[(int)S[i]]] + 1;
    }
    
    H[0] = 0;
    for (i = 0; i < histlen; i = i + 1) {
        H_num[0] = hist[i];
        H_den[0] = len;
        n = 0;
        temp = H_num[0];
        while (temp > 1) {
            temp = temp / 2;
            n = n + 1;
        }
        H[0] = H[0] - (H_num[0] * n) / H_den[0];
    }
    
    return H[0];
}
