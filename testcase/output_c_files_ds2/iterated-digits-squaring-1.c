int is89(int x[5]) {
    while (1) {
        int s[5] = {0};
        do {
            s[0] = s[0] + ((x[0] % 10) * (x[0] % 10));
            x[0] = x[0] / 10;
        } while (x[0] != 0);

        if (s[0] == 89) {
            return 1;
        }
        if (s[0] == 1) {
            return 0;
        }
        x[0] = s[0];
    }
    return;
}

void func(int n1, int n2, int sums[2593]) {
    sums[0] = 1;
    for (int i = 1; i < 2593; i = i + 1) {
        sums[i] = 0;
    }

    for (int n = 1; n < 5; n = n + 1) {
        for (int i = n * 81; i > 0; i = i - 1) {
            for (int j = 1; j < 10; j = j + 1) {
                int s = j * j;
                if (s > i) {
                    break;
                }
                sums[i] = sums[i] + sums[i - s];
            }
        }

        int count89[5] = {0};
        for (int i = 1; i < n * 81 + 1; i = i + 1) {
            int x[5] = {i};
            if (!is89(x)) {
                continue;
            }

            if (sums[i] > 4294967295 - count89[0]) {
                return;
            }
            count89[0] = count89[0] + sums[i];
        }
    }
    return;
}
