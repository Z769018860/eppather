int x(int i) {
    static int _n = 1;
    _n = _n + i;
    return _n;
}

int y(int i) {
    static int _n = 3;
    _n = _n + i;
    return _n;
}

int z(int i) {
    static int _n = 97;
    _n = _n + i;
    return _n;
}

void accumulator() {
    return;
}
