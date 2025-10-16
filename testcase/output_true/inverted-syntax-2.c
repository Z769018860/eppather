int foo();

void rewritten_function() {
    int a[5];
    a[0] = 0;
    int _o[5];
    _o[0] = 2;
    
    for (int i = 0; i < 1; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            if (_o[0] == 1) {
                a[0] = 4;
            }
            if (_o[0] == 0) {
                break;
            }
            if (_o[0] == 2) {
                _o[0] = !!(foo());
                continue;
            }
            break;
        }
    }
    return;
}
