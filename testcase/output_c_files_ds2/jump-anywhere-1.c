void func(int x) {
    int result[5];
    if (x > 0) {
        result[0] = 1;
    } else {
        result[0] = 0;
    }
    if (result[0] == 1) {
        for (int i = 0; i < 5; i = i + 1) {
            result[i] = 1;
        }
    } else {
        for (int i = 0; i < 5; i = i + 1) {
            result[i] = 0;
        }
    }
    for (int i = 0; i < 5; i = i + 1) {
        result[i] = result[i] + 1;
    }
    return;
}
