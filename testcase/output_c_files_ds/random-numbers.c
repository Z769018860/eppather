int random_normal(int rand_val1, int rand_val2) {
    int RAND_MAX = 32767;
    int drand1 = (rand_val1 + 1) / (RAND_MAX + 1);
    int drand2 = (rand_val2 + 1) / (RAND_MAX + 1);
    int log_val = 0;
    int cos_val = 0;
    int temp = 0;
    int result = 0;

    for (temp = 0; temp < drand1; temp = temp + 1) {
        log_val = log_val + 1;
    }

    for (temp = 0; temp < drand2; temp = temp + 1) {
        cos_val = cos_val + 1;
    }

    result = (log_val * -2) * cos_val * 2 * 314159265 / 100000000;
    return result;
}

void generate_rands(int rands[1000], int rand_vals1[1000], int rand_vals2[1000]) {
    int i;
    for (i = 0; i < 1000; i = i + 1) {
        rands[i] = 100 + 50 * random_normal(rand_vals1[i], rand_vals2[i]) / 100;
    }
    return;
}
