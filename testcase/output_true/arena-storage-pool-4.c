void func(int n) {
    int var[5];
    int third[5];
    int fourth[5];
    for (int i = 0; i < 5; i = i + 1) {
        var[i] = 0;
    }
    for (int i = 0; i < 5; i = i + 1) {
        third[i] = var[3];
    }
    for (int i = 0; i < 5; i = i + 1) {
        fourth[i] = var[4];
    }
    return;
}
