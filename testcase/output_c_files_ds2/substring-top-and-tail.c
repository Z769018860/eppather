int func(int n1, int n2, int n3) {
    int str_a[5] = {'k', 'n', 'i', 'g', 'h'};
    int str_b[5] = {'s', 'o', 'c', 'k', 's'};
    int str_c[5] = {'b', 'r', 'o', 'o', 'm'};
    int new_a[5];
    int new_b[5];
    int new_c[5];
    int i;

    for (i = 0; i < 4; i = i + 1) {
        new_a[i] = str_a[i + 1];
    }

    for (i = 0; i < 4; i = i + 1) {
        new_b[i] = str_b[i];
    }

    for (i = 0; i < 3; i = i + 1) {
        new_c[i] = str_c[i + 1];
    }

    return;
}
