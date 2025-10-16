void deal(int s, int *t) {
    int i;
    int j;
    int temp;
    int seed;
    int rmax32;
    seed = s;
    rmax32 = 2147483647;
    for (i = 0; i < 52; i = i + 1) {
        t[i] = 51 - i;
    }
    for (i = 0; i < 51; i = i + 1) {
        seed = (seed * 214013 + 2531011) & rmax32;
        j = 51 - (seed >> 16) % (52 - i);
        temp = t[i];
        t[i] = t[j];
        t[j] = temp;
    }
    return;
}
