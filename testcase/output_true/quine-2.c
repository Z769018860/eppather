void quine(int n1, int n2, int n3, int n4, int n5) {
    int c[5] = {35, 105, 110, 99, 108};
    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (i == 0) {
            c[i] = 35;
        } else if (i == 1) {
            c[i] = 105;
        } else if (i == 2) {
            c[i] = 110;
        } else if (i == 3) {
            c[i] = 99;
        } else if (i == 4) {
            c[i] = 108;
        }
    }
    return;
}
