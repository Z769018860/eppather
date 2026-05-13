int accumulator_x(int i) {
    static int _n[5];
    _n[0] = 1;
    _n[0] = _n[0] + i;
    return _n[0];
}

int accumulator_y(int i) {
    static int _n[5];
    _n[0] = 3;
    _n[0] = _n[0] + i;
    return _n[0];
}

int accumulator_z(int i) {
    static int _n[5];
    _n[0] = 97;
    _n[0] = _n[0] + i;
    return _n[0];
}

void accumulator_combined(int i, int selector) {
    static int _n_x[5];
    static int _n_y[5];
    static int _n_z[5];
    if (selector == 0) {
        _n_x[0] = 1;
        _n_x[0] = _n_x[0] + i;
    } else if (selector == 1) {
        _n_y[0] = 3;
        _n_y[0] = _n_y[0] + i;
    } else if (selector == 2) {
        _n_z[0] = 97;
        _n_z[0] = _n_z[0] + i;
    }
    return;
}
