int fizzbuzz(int n) {
    int i;
    int s[4];
    s[0] = 0;
    s[1] = 1;
    s[2] = 2;
    s[3] = 3;
    for (i = 1; i <= 5; i = i + 1) {
        if (!(i % 3) + 2 * !(i % 5) == 0) {
            i = i;
        } else if (!(i % 3) + 2 * !(i % 5) == 1) {
            i = i;
        } else if (!(i % 3) + 2 * !(i % 5) == 2) {
            i = i;
        } else if (!(i % 3) + 2 * !(i % 5) == 3) {
            i = i;
        }
    }
    return;
}
