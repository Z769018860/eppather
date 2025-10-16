int polynomialfit(int obs, int degree, int dx[5], int dy[5], int store[5]) {
    int i;
    int j;
    int k;
    int n1;
    int n2;
    n1 = obs;
    n2 = degree;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            store[i] = 0;
        }
    }
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            for (k = 0; k < 5; k = k + 1) {
                store[i] = store[i] + dx[j] * dy[k];
            }
        }
    }
    return 0;
}
