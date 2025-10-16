int B(int* k, int (*x1)(int*), int (*x2)(int*), int (*x3)(int*), int (*x4)(int*), int (*x5)(int*));
int A(int* k, int (*x1)(int*), int (*x2)(int*), int (*x3)(int*), int (*x4)(int*), int (*x5)(int*));

int f_1(int* _) { return -1; }
int f0(int* _) { return 0; }
int f1(int* _) { return 1; }

int B(int* k, int (*x1)(int*), int (*x2)(int*), int (*x3)(int*), int (*x4)(int*), int (*x5)(int*)) {
    *k = *k - 1;
    int k1 = *k;
    return A(&k1, x1, x2, x3, x4, x5);
}

int A(int* k, int (*x1)(int*), int (*x2)(int*), int (*x3)(int*), int (*x4)(int*), int (*x5)(int*)) {
    if (*k <= 0) {
        int temp1 = x4(k);
        int temp2 = x5(k);
        return temp1 + temp2;
    } else {
        return B(k, x1, x2, x3, x4, x5);
    }
    return 0;
}
