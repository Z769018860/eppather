int is_prime(int n) {
    int i;
    int j;
    if (n <= 1) {
        return 0;
    }
    for (i = 2; i * i <= n; i = i + 1) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int is_palindrome(int n) {
    int reversed = 0;
    int original = n;
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n = n / 10;
    }
    return original == reversed;
}

void find_emirp() {
    int left = 998443;
    int right = 739399;
    int count = 0;
    int i;
    for (i = left; i >= right; i = i - 1) {
        if (is_prime(i) && is_palindrome(i)) {
            count = count + 1;
        }
    }
    return;
}
