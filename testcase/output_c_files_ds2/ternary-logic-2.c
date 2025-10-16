int t_not(int a) { return -a; }
int t_and(int a, int b) { if (a < b) { return a; } else { return b; } }
int t_or(int a, int b) { if (a > b) { return a; } else { return b; } }
int t_eq(int a, int b) { return a * b; }
int t_imply(int a, int b) { if (-a > b) { return -a; } else { return b; } }
void show_op(int (*f)(int, int)) {
    int a[5];
    int b[5];
    int i;
    int j;
    for (i = 0; i < 5; i = i + 1) {
        a[i] = 0;
        b[i] = 0;
    }
    a[0] = -1;
    for (i = 0; i < 5; i = i + 1) {
        b[0] = -1;
        for (j = 0; j < 5; j = j + 1) {
            f(a[0], b[0]);
            b[0] = b[0] + 1;
            if (b[0] > 1) { break; }
        }
        a[0] = a[0] + 1;
        if (a[0] > 1) { break; }
    }
    return;
}
