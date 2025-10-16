void shuffle(int* obj, int nmemb, int size) {
    int temp[5];
    int n;
    int k;
    int i;
    int j;
    n = nmemb;
    for (i = 0; i < 5; i = i + 1) {
        if (n > 1) {
            k = (int)((double)n * (12345 / (32767 + 1.0)));
            n = n - 1;
            for (j = 0; j < 5; j = j + 1) {
                temp[j] = *(obj + n * size + j);
                *(obj + n * size + j) = *(obj + k * size + j);
                *(obj + k * size + j) = temp[j];
            }
        }
    }
    return;
}
