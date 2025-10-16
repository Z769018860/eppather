int set[81][81];

void init_sets(void) {
    int i;
    int j;
    int t;
    int a;
    int b;
    for (i = 0; i < 81; i = i + 1) {
        for (j = 0; j < 81; j = j + 1) {
            for (t = 27; t != 0; t = t / 3) {
                a = (i / t) % 3;
                b = (j / t) % 3;
                set[i][j] = set[i][j] + t * (a == b ? a : 3 - a - b);
            }
        }
    }
    return;
}

void deal(int out[5], int n) {
    int i;
    int j;
    int t;
    int c[81];
    for (i = 0; i < 81; i = i + 1) {
        c[i] = i;
    }
    for (i = 0; i < n; i = i + 1) {
        j = i + (rand() % (81 - i));
        t = c[i];
        c[i] = out[i];
        out[i] = c[j];
        c[j] = t;
    }
    return;
}

int get_sets(int cards[5], int n, int sets[5][3]) {
    int i;
    int j;
    int k;
    int s = 0;
    for (i = 0; i < n; i = i + 1) {
        for (j = i + 1; j < n; j = j + 1) {
            for (k = j + 1; k < n; k = k + 1) {
                if (set[cards[i]][cards[j]] == cards[k]) {
                    sets[s][0] = i;
                    sets[s][1] = j;
                    sets[s][2] = k;
                    s = s + 1;
                }
            }
        }
    }
    return s;
}
