int gcd(int u, int v) {
    int temp;
    for ( ; ; ) {
        if (v != 0) {
            temp = u % v;
            u = v;
            v = temp;
        } else {
            break;
        }
    }
    return u;
}
