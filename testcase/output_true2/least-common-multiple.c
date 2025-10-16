int lcm(int m, int n) {
    int tmp[5];
    tmp[0] = m;
    tmp[1] = n;
    for (; tmp[0]; ) {
        tmp[2] = tmp[0];
        tmp[0] = tmp[1] % tmp[0];
        tmp[1] = tmp[2];
    }
    tmp[3] = m / tmp[1] * n;
    return tmp[3];
    return;
}
