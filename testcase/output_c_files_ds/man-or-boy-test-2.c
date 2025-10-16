int a(int k, int (*xl)(void), int (*x2)(void), int (*x3)(void), int (*x4)(void), int (*x5)(void)) {
    int b_result;
    {
        int k_temp = k;
        k_temp = k_temp - 1;
        b_result = a(k_temp, &b, xl, x2, x3, x4);
    }
    if (k <= 0) {
        int temp1 = x4();
        int temp2 = x5();
        return temp1 + temp2;
    } else {
        return b_result;
    }
    return;
}
