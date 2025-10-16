int flip_coin(int n) {
    int results[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        results[i] = (i * 1103515245 + 12345) % 2;
    }
    return;
}
