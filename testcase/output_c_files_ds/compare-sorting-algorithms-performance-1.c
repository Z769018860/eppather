int fillconst;

void fillwithconst(int *v, int n) {
    for (int i = 0; i < n; i = i + 1) {
        v[i] = fillconst;
    }
    return;
}

void fillwithrrange(int *v, int n) {
    for (int i = 0; i < n; i = i + 1) {
        v[i] = n - i - 1;
    }
    return;
}

void shuffledrange(int *v, int n) {
    int j;
    int temp;
    fillwithrrange(v, n);
    for (int i = 0; i < n; i = i + 1) {
        j = (i * 31 + 7) % n;
        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
    return;
}
