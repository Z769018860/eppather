int fillwithconst(int v[5], int n, int fill_constant) {
    for (int i = 0; i < 5; i = i + 1) {
        v[i] = fill_constant;
    }
    return;
}

int fillwithrrange(int v[5], int n) {
    for (int i = 0; i < 5; i = i + 1) {
        v[i] = 5 - i;
    }
    return;
}

int shuffledrange(int v[5], int n) {
    fillwithrrange(v, 5);
    for (int i = 0; i < 5; i = i + 1) {
        int r = 3 % 5;
        int t = v[i];
        v[i] = v[r];
        v[r] = t;
    }
    return;
}
