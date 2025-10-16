void compose_functor(int f[5], int g[5], int result[5]) {
    for (int i = 0; i < 5; i = i + 1) {
        result[i] = f[g[i]];
    }
    return;
}
