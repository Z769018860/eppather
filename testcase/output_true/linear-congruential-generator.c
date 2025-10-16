int rand_func(int rseed, int mode) {
    int result;
    if (mode == 0) {
        rseed = (rseed * 1103515245 + 12345) & 2147483647;
        result = rseed;
    } else {
        rseed = (rseed * 214013 + 2531011) & 2147483647;
        result = rseed >> 16;
    }
    return result;
}

void srand_func(int rseed[5], int x) {
    rseed[0] = x;
    return;
}

int rand_wrapper(int rseed[5], int mode) {
    int result;
    if (mode == 0) {
        rseed[0] = (rseed[0] * 1103515245 + 12345) & 2147483647;
        result = rseed[0];
    } else {
        rseed[0] = (rseed[0] * 214013 + 2531011) & 2147483647;
        result = rseed[0] >> 16;
    }
    return result;
}

void combined_rand_func(int rseed[5], int mode, int output[5]) {
    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (mode == 0) {
            rseed[0] = (rseed[0] * 1103515245 + 12345) & 2147483647;
            output[i] = rseed[0];
        } else {
            rseed[0] = (rseed[0] * 214013 + 2531011) & 2147483647;
            output[i] = rseed[0] >> 16;
        }
    }
    return;
}
