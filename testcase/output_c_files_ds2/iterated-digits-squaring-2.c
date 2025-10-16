int choose_sum_and_count_89(int* got, int n_chosen, int len, int at, int max_types, int* count89) {
    int digits[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i;
    long count = 0;
    int digitcounts[10];
    for (i = 0; i < 10; i = i + 1) {
        digitcounts[i] = 0;
    }
    if (n_chosen == len) {
        if (!got) {
            return 1;
        }
        int sum = 0;
        for (i = 0; i < len; i = i + 1) {
            int digit = digits[got[i]];
            digitcounts[digit] = digitcounts[digit] + 1;
            sum = sum + digit * digit;
        }
        if (sum == 0) {
            return 1;
        }
        if ((sum != 1) && (sum != 89)) {
            while ((sum != 1) && (sum != 89)) {
                int num = sum;
                sum = 0;
                while (num > 0) {
                    int digit = num % 10;
                    num = (num - digit) / 10;
                    sum = sum + digit * digit;
                }
            }
        }
        if (sum == 89) {
            int count_this_comb = 1;
            for (i = 1; i <= len; i = i + 1) {
                count_this_comb = count_this_comb * i;
            }
            for (i = 0; i < 10; i = i + 1) {
                int fact = 1;
                for (int j = 1; j <= digitcounts[i]; j = j + 1) {
                    fact = fact * j;
                }
                count_this_comb = count_this_comb / fact;
            }
            *count89 = *count89 + count_this_comb;
        }
        return 1;
    }
    for (i = at; i < max_types; i = i + 1) {
        if (got) {
            got[n_chosen] = i;
        }
        count = count + choose_sum_and_count_89(got, n_chosen + 1, len, i, max_types, count89);
    }
    return count;
}
