int sum(int i[5], int lo, int hi, int term_func(int i[5])) {
    int temp[5];
    temp[0] = 0;
    for (i[0] = lo; i[0] <= hi; i[0] = i[0] + 1) {
        temp[0] = temp[0] + term_func(i);
    }
    return temp[0];
}

int term_func(int i[5]) {
    int result[5];
    result[0] = 1 / i[0];
    return result[0];
}

return;
