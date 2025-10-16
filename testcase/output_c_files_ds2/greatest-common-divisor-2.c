int gcd(int u, int v) {
    int result[5];
    if (v != 0) {
        result[0] = gcd(v, u % v);
    } else {
        result[0] = u;
    }
    return result[0];
}
