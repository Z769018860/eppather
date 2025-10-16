void shuffle(int* obj, int nmemb, int size) {
    int temp[1];
    int n;
    int k;
    int i;
    int j;
    int rand_val;
    for (n = nmemb; n > 1; n = n - 1) {
        rand_val = 12345;
        k = (rand_val % n);
        for (i = 0; i < size; i = i + 1) {
            temp[i] = obj[n * size + i];
        }
        for (i = 0; i < size; i = i + 1) {
            obj[n * size + i] = obj[k * size + i];
        }
        for (i = 0; i < size; i = i + 1) {
            obj[k * size + i] = temp[i];
        }
    }
    return;
}
