int filter(int img[5], int K[5], int Ks, int n1, int n2) {
    int result[5];
    int i;
    int j;
    int k;
    int l;
    int sum;
    int x;
    int y;
    int halfKs;
    halfKs = Ks / 2;
    for (i = 0; i < 5; i = i + 1) {
        result[i] = 0;
    }
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            sum = 0;
            for (k = 0; k < 5; k = k + 1) {
                for (l = 0; l < 5; l = l + 1) {
                    x = i - halfKs + k;
                    y = j - halfKs + l;
                    if (x >= 0) {
                        if (x < 5) {
                            if (y >= 0) {
                                if (y < 5) {
                                    sum = sum + img[x * 5 + y] * K[k * 5 + l];
                                }
                            }
                        }
                    }
                }
            }
            result[i * 5 + j] = sum;
        }
    }
    return;
}
