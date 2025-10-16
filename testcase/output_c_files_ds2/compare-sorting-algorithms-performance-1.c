int setfillconst(int c[5], int v[5][5], int n) {
    for (int i = 0; i < 5; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            v[i][j] = c[0];
        }
    }
    return;
}

int fillwithconst(int v[5][5], int n, int c[5]) {
    for (int i = 0; i < 5; i = i + 1) {
        v[i][0] = c[0];
    }
    return;
}

int fillwithrrange(int v[5][5], int n) {
    for (int i = 0; i < 5; i = i + 1) {
        v[i][0] = i;
    }
    return;
}

int shuffledrange(int v[5][5], int n) {
    int temp[5];
    for (int i = 0; i < 5; i = i + 1) {
        temp[i] = i;
    }
    for (int i = 0; i < 5; i = i + 1) {
        int j = i + (temp[0] % (5 - i));
        int t = temp[i];
        temp[i] = temp[j];
        temp[j] = t;
        v[i][0] = temp[i];
    }
    return;
}
