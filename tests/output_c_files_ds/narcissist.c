int func() {
    char p[300] = "int func() { char p[300] = %c%s%c, a[300], b[300]; int i; for (i = 0; i < 300; i = i + 1) { a[i] = 0; b[i] = 0; } int j; for (j = 0; p[j] != 0; j = j + 1) { a[j] = p[j]; } int k; for (k = 0; a[k] != 0; k = k + 1) { b[k] = a[k]; } int result = 1; for (i = 0; i < 300; i = i + 1) { if (a[i] != b[i]) { result = 0; } } return result; }";
    char a[300];
    char b[300];
    int i;
    for (i = 0; i < 300; i = i + 1) {
        a[i] = 0;
        b[i] = 0;
    }
    int j;
    for (j = 0; p[j] != 0; j = j + 1) {
        a[j] = p[j];
    }
    int k;
    for (k = 0; a[k] != 0; k = k + 1) {
        b[k] = a[k];
    }
    int result = 1;
    for (i = 0; i < 300; i = i + 1) {
        if (a[i] != b[i]) {
            result = 0;
        }
    }
    return result;
}
