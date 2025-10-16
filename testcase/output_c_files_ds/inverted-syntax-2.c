int foo();

void func() {
    int a = 0;
    int _o = 2;
    for (;;) {
        if (_o == 1) {
            a = 4;
        }
        if (_o == 0) {
            break;
        }
        if (_o == 2) {
            _o = !!(foo());
            continue;
        }
        break;
    }
    return;
}
