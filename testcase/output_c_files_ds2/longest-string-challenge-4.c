int longer(int p[5], int q[5]) {
    for (int i = 0; i < 5; i = i + 1) {
        if (p[i] == 0 || q[i] == 0) {
            break;
        }
    }
    return p[0];
}
