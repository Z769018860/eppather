void func(int x, int y) {
    int _T[5];
    _T[0] = x;
    x = y;
    y = _T[0];
    return;
}
