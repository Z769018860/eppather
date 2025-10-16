int* binomCoeff(int n) {
    int b[5];
    int j;
    b[0] = n%2 ? -1 : 1;
    for (j=1; j<=n; j=j+1) {
        b[j] = -b[j-1]*(n+1-j)/j;
    }
    int* result = b;
    return result;
}

void combined(int p, int lenArray, int array[5]) {
    int b[5];
    int j;
    int k;
    b[0] = p%2 ? -1 : 1;
    for (j=1; j<=p; j=j+1) {
        b[j] = -b[j-1]*(p+1-j)/j;
    }
    for (k=0; k<5; k=k+1) {
        array[k] = array[k] * b[0];
        for (j=1; j<=p; j=j+1) {
            array[k] = array[k] + b[j] * array[k+j];
        }
    }
    return;
}
