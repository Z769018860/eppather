int SumDigits(int n, int base) {
    int sum[5];
    sum[0] = 0;
    for (; n; n = n / base) {
        sum[0] = sum[0] + n % base;
    }
    return sum[0];
}
