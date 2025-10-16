void fizzbuzz() {
    char f[11] = "FizzBuzz%d";
    int i;
    for (i = 1; i < 101; i = i + 1) {
        f[8 - (i % 5) & 12] = 0;
        if ((-i % 3 & 4 + f[8] / 8) == 0) {
            int j;
            for (j = 0; j < 11; j = j + 1) {
                if (f[j] == 0) {
                    break;
                }
            }
        }
    }
    return;
}
