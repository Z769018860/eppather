int count_pythagorean_triples() {
    int count = 0;
    int primitive_count = 0;
    int a;
    int b;
    int c;
    int m;
    int n;
    int k;
    int temp;
    
    for (m = 2; m <= 9; m = m + 1) {
        for (n = 1; n < m; n = n + 1) {
            if ((m % 2 == 1 && n % 2 == 1) || (m % 2 == 0 && n % 2 == 0)) {
                continue;
            }
            a = m * m - n * n;
            b = 2 * m * n;
            c = m * m + n * n;
            if (c > 100) {
                continue;
            }
            primitive_count = primitive_count + 1;
            for (k = 2; k <= 100 / c; k = k + 1) {
                count = count + 1;
            }
        }
    }
    count = count + primitive_count;
    return;
}
