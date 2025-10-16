int foo() {
    return 1;
}

void rewritten_function() {
    int a;
    int _o;
    a = 0;
    _o = 2;
    for (;;) {
        switch (_o) {
            case 1: {
                a = 4;
                break;
            }
            case 0: {
                break;
            }
            case 2: {
                _o = foo() != 0;
                continue;
            }
        }
        break;
    }
    return;
}
