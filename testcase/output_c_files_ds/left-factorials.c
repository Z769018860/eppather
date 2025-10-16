void left_factorial(int rop[100], int op) {
    int t1[100] = {0};
    t1[0] = 1;
    for (int i = 0; i < 100; i = i + 1) {
        rop[i] = 0;
    }

    for (int i = 1; i <= op; i = i + 1) {
        int carry = 0;
        for (int j = 0; j < 100; j = j + 1) {
            int sum = rop[j] + t1[j] + carry;
            rop[j] = sum % 10;
            carry = sum / 10;
        }

        carry = 0;
        for (int j = 0; j < 100; j = j + 1) {
            int product = t1[j] * i + carry;
            t1[j] = product % 10;
            carry = product / 10;
        }
    }
    return;
}
