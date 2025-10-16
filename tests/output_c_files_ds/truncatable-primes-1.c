int sieve_and_check() {
    int primes[1000000];
    int i;
    int j;
    for (i = 0; i < 1000000; i = i + 1) {
        primes[i] = 1;
    }
    primes[0] = 0;
    primes[1] = 0;
    i = 2;
    for (; i * i < 1000000; ) {
        for (j = i * 2; j < 1000000; j = j + i) {
            primes[j] = 0;
        }
        i = i + 1;
        for (; i < 1000000 && !primes[i]; i = i + 1) {
        }
    }

    int max_left = 0;
    int max_right = 0;
    int n;
    for (n = 999999; !max_left; n = n - 2) {
        int tens = 1;
        int temp_n = n;
        for (; tens < temp_n; tens = tens * 10) {
        }
        int is_left = 1;
        temp_n = n;
        for (; temp_n; ) {
            if (!primes[temp_n]) {
                is_left = 0;
                break;
            }
            tens = tens / 10;
            if (temp_n < tens) {
                is_left = 0;
                break;
            }
            temp_n = temp_n % tens;
        }
        if (is_left) {
            max_left = n;
        }
    }

    for (n = 999999; !max_right; n = n - 2) {
        int is_right = 1;
        int temp_n = n;
        for (; temp_n; temp_n = temp_n / 10) {
            if (!primes[temp_n]) {
                is_right = 0;
                break;
            }
        }
        if (is_right) {
            max_right = n;
        }
    }

    return;
}
