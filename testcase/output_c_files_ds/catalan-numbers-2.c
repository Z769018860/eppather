int catalan(int n) {
    int factorial(int x) {
        if (x == 0) {
            return 1;
        }
        return x * factorial(x - 1);
    }

    int firstOption(int n) {
        int topMultiplier = 2;
        return factorial(topMultiplier * n) / (factorial(n + 1) * factorial(n));
    }

    int secondOption(int n) {
        if (n == 0) {
            return 1;
        }
        int sum = 0;
        int i = 0;
        for (i = 0; i <= (n - 1); i = i + 1) {
            sum = sum + secondOption(i) * secondOption((n - 1) - i);
        }
        return sum;
    }

    int thirdOption(int n) {
        if (n == 0) {
            return 1;
        }
        return ((2 * (2 * n - 1)) / (n + 1)) * thirdOption(n - 1);
    }

    int result = firstOption(n);
    result = secondOption(n);
    result = thirdOption(n);
    return result;
}
