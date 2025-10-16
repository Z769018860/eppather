int factorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

unsigned int sum_square_digits(unsigned int n) {
    int num = n;
    int sum = 0;
    for (; num > 0; ) {
        int digit = num % 10;
        num = (num - digit) / 10;
        sum = sum + digit * digit;
    }
    return sum;
}

void choose_sum_and_count_89(int * got, int n_chosen, int len, int at, int max_types, int * count89) {
    int digitcounts[10];
    int i;
    for (i = 0; i < 10; i = i + 1) {
        digitcounts[i] = 0;
    }
    if (n_chosen == len) {
        if (got) {
            int sum = 0;
            for (i = 0; i < len; i = i + 1) {
                int digits[10] = {0,1,2,3,4,5,6,7,8,9};
                int digit = digits[got[i]];
                digitcounts[digit] = digitcounts[digit] + 1;
                sum = sum + digit * digit;
            }
            if (sum == 0) {
                return;
            }
            if ((sum != 1) && (sum != 89)) {
                while ((sum != 1) && (sum != 89)) {
                    sum = sum_square_digits(sum);
                }
            }
            if (sum == 89) {
                int count_this_comb = factorial(len);
                for (i = 0; i < 10; i = i + 1) {
                    count_this_comb = count_this_comb / factorial(digitcounts[i]);
                }
                *count89 = *count89 + count_this_comb;
            }
        }
        return;
    }
    for (i = at; i < max_types; i = i + 1) {
        if (got) {
            got[n_chosen] = i;
        }
        choose_sum_and_count_89(got, n_chosen + 1, len, i, max_types, count89);
    }
    return;
}
