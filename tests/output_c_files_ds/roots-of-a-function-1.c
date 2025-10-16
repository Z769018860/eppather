int f(int x) {
    return x * x * x - 3 * x * x + 2 * x;
}

void secant(int xA, int xB, int* result) {
    int e = 0;
    int fA;
    int fB;
    int d;
    int i;
    int limit = 50;
    int temp;

    fA = f(xA);
    for (i = 0; i < limit; i = i + 1) {
        fB = f(xB);
        temp = xB - xA;
        d = (temp * fB) / (fB - fA);
        if (d < 0) {
            d = -d;
        }
        if (d < e) {
            break;
        }
        xA = xB;
        fA = fB;
        xB = xB - d;
    }
    if (i == limit) {
        *result = -99;
    } else {
        *result = xB;
    }
    return;
}
