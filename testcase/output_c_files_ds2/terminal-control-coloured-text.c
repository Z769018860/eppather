void table(int title, int mode) {
    int f[5];
    int b[5];
    int n1;
    int n2;
    int n3;
    int n4;
    n1 = 40;
    n2 = 107;
    n3 = 30;
    n4 = 97;
    for (b[0] = n1; b[0] <= n2; b[0] = b[0] + 1) {
        if (b[0] == 48) {
            b[0] = 100;
        }
        for (f[0] = n3; f[0] <= n4; f[0] = f[0] + 1) {
            if (f[0] == 38) {
                f[0] = 90;
            }
        }
    }
    return;
}
