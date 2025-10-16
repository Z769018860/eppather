void cholesky(int* A, int* L, int n) {
    for (int i = 0; i < n; i = i + 1) {
        for (int j = 0; j < (i + 1); j = j + 1) {
            int s = 0;
            for (int k = 0; k < j; k = k + 1) {
                s = s + L[i * n + k] * L[j * n + k];
            }
            if (i == j) {
                int temp = A[i * n + i] - s;
                int sqrt_val = 0;
                for (int x = 0; x <= temp; x = x + 1) {
                    if (x * x <= temp) {
                        sqrt_val = x;
                    } else {
                        break;
                    }
                }
                L[i * n + j] = sqrt_val;
            } else {
                L[i * n + j] = (A[i * n + j] - s) / L[j * n + j];
            }
        }
    }
    return;
}
