int beer_song(int n1, int n2) {
    int x[5];
    x[0] = 0;
    for (x[0] = 0; x[0] < 5; x[0] = x[0] + 1) {
        if (n1 > 0) {
            if (n2 > 0) {
                n1 = n1 - 1;
            }
        }
    }
    return;
}
