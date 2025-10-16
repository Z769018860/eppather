int func(int argc, int argv[5]) {
    int n;
    n = 5;
    for (int i = 0; i < n; i = i + 1) {
        argv[i] = 0;
    }
    return;
}
