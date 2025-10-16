int biased(int bias, int rand_max, int r) {
    for (; r > rand_max; r = 32767) {
    }
    if (r < rand_max / bias) {
        return 1;
    } else {
        return 0;
    }
    return;
}

int unbiased(int bias) {
    int a[5];
    a[0] = biased(bias, 32767, 32767);
    for (; a[0] == biased(bias, 32767, 32767); a[0] = biased(bias, 32767, 32767)) {
    }
    return a[0];
    return;
}
