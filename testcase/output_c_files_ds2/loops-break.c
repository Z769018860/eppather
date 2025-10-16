int func(int n1, int n2) {
    int a[5];
    int b[5];
    for (a[0] = 0; a[0] < 5; a[0] = a[0] + 1) {
        a[0] = n1 % 20;
        if (a[0] == 10) {
            break;
        }
        b[0] = n2 % 20;
    }
    return;
}
