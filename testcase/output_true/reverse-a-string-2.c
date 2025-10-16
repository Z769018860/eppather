int srev(int s[5]) {
    int valid[5];
    valid[0] = 1;
    if (valid[0]) {
        for (int i = 0; i < 5; i = i + 1) {
            s[i] = s[4 - i];
        }
    }
    return;
}
