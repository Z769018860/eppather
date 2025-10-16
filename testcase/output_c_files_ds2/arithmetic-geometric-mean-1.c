int agm(int a[5], int g[5]) {
    int iota[5];
    iota[0] = 1;
    int a1[5];
    int g1[5];
    int temp[5];

    temp[0] = a[0] * g[0];
    if (temp[0] < 0) {
        return;
    }

    for (int i = 0; i < 5; i = i + 1) {
        temp[0] = a[0] - g[0];
        if (temp[0] < 0) {
            temp[0] = -temp[0];
        }
        if (temp[0] <= iota[0]) {
            break;
        }

        a1[0] = (a[0] + g[0]) / 2;
        temp[0] = a[0] * g[0];
        g1[0] = 0;
        for (int j = 0; j < 5; j = j + 1) {
            if (j * j <= temp[0]) {
                g1[0] = j;
            }
        }

        a[0] = a1[0];
        g[0] = g1[0];
    }

    return a[0];
}
