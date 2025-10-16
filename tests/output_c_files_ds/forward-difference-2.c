int* binomCoeff(int n) {
    int b[100];
    int j;
    for (j = 0; j <= n; j = j + 1) {
        b[j] = 0;
    }
    if (n % 2 != 0) {
        b[0] = -1;
    } else {
        b[0] = 1;
    }
    for (j = 1; j <= n; j = j + 1) {
        b[j] = -b[j - 1] * (n + 1 - j) / j;
    }
    return b;
}

void computeDifference(int array[100], int lenArray, int p) {
    int b[100];
    int j;
    int k;
    for (j = 0; j <= p; j = j + 1) {
        b[j] = 0;
    }
    if (p % 2 != 0) {
        b[0] = -1;
    } else {
        b[0] = 1;
    }
    for (j = 1; j <= p; j = j + 1) {
        b[j] = -b[j - 1] * (p + 1 - j) / j;
    }
    for (k = 0; k < lenArray; k = k + 1) {
        array[k] = array[k] * b[0];
        for (j = 1; j <= p; j = j + 1) {
            array[k] = array[k] + b[j] * array[k + j];
        }
    }
    return;
}
