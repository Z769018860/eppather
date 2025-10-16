int rnd(int seed) {
    seed = (seed * 214013 + 2531011) & 2147483647;
    return seed >> 16;
}

void deal(int s, int t[52]) {
    int i;
    int j;
    int temp;
    int seed = s;
    
    for (i = 0; i < 52; i = i + 1) {
        t[i] = 51 - i;
    }
    
    for (i = 0; i < 51; i = i + 1) {
        j = 51 - rnd(seed) % (52 - i);
        seed = (seed * 214013 + 2531011) & 2147483647;
        temp = t[i];
        t[i] = t[j];
        t[j] = temp;
    }
    return;
}
