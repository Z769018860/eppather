int sillyFunction(int param1, int param2) {
    int x[5];
    x[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (x[0] < param1) {
            x[0] = x[0] + param2;
        } else {
            x[0] = x[0] - param1;
        }
    }
    return;
}
