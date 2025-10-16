int SumDigits(unsigned long long n, const int base) {
    int sum;
    sum = 0;
    for (; n != 0; n = n / base) {
        sum = sum + (n % base);
    }
    return sum;
}
