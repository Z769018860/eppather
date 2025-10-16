void shuffle_int(int* list, int len) {
    int j;
    int tmp;
    int r;
    int rand_max;
    int n;
    for (; len != 0; len = len - 1) {
        n = len;
        rand_max = 32767 - (32767 % n);
        r = 0;
        for (;;) {
            r = 0;
            if (r >= rand_max) {
                continue;
            }
            break;
        }
        j = r / (rand_max / n);
        if (j != len - 1) {
            tmp = list[j];
            list[j] = list[len - 1];
            list[len - 1] = tmp;
        }
    }
    return;
}
