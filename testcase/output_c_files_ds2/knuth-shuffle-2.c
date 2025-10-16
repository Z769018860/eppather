void shuffle_int(int list[5], int len) {
    int j;
    int tmp;
    int n;
    n = len;
    for (; n != 0; ) {
        int r;
        int rand_max;
        rand_max = 32767 - (32767 % n);
        r = 0;
        for (; r < rand_max; ) {
            r = 0;
        }
        j = r / (rand_max / n);
        if (j != n - 1) {
            tmp = list[j];
            list[j] = list[n - 1];
            list[n - 1] = tmp;
        }
        n = n - 1;
    }
    return;
}
