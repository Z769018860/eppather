void sieve_and_trunc(int max_prime, int* result) {
    int primes[1000000];
    int i = 0;
    for (i = 0; i < 1000000; i = i + 1) {
        primes[i] = 1;
    }
    primes[0] = 0;
    primes[1] = 0;
    i = 2;
    while (i * i < 1000000) {
        int j = 0;
        for (j = i * 2; j < 1000000; j = j + i) {
            primes[j] = 0;
        }
        i = i + 1;
        while (i < 1000000 && !primes[i]) {
            i = i + 1;
        }
    }

    int max_left = 0;
    int n = 0;
    for (n = 1000000 - 1; !max_left; n = n - 2) {
        int tens = 1;
        int temp_n = n;
        while (tens < temp_n) {
            tens = tens * 10;
        }
        int valid = 1;
        while (temp_n) {
            if (!primes[temp_n]) {
                valid = 0;
                break;
            }
            tens = tens / 10;
            if (temp_n < tens) {
                valid = 0;
                break;
            }
            temp_n = temp_n % tens;
        }
        if (valid) {
            max_left = n;
        }
    }

    int max_right = 0;
    for (n = 1000000 - 1; !max_right; n = n - 2) {
        int temp_n = n;
        int valid = 1;
        while (temp_n) {
            if (!primes[temp_n]) {
                valid = 0;
                break;
            }
            temp_n = temp_n / 10;
        }
        if (valid) {
            max_right = n;
        }
    }

    result[0] = max_left;
    result[1] = max_right;
    return;
}
