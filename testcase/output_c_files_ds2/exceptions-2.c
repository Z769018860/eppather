void f(int exp[5]) {
    int exception_outer[5];
    int exception_inner[5];
    int exception[5];
    int a[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        exception_outer[i] = exp[i];
    }
    for (i = 0; i < 5; i = i + 1) {
        exp[i] = exception_inner[i];
    }
    exception[0] = 0;
    if (exception[0] == 0) {
        for (i = 0; i < 5; i = i + 1) {
            exp[i] = exception_outer[i];
        }
    } else {
        for (i = 0; i < 5; i = i + 1) {
            exp[i] = exception_outer[i];
        }
        if (exception[0] == 1) {
            a[0] = 50;
            for (i = 0; i < 5; i = i + 1) {
                exp[i] = exception_outer[i];
            }
        } else {
            for (i = 0; i < 5; i = i + 1) {
                exp[i] = exception_outer[i];
            }
        }
    }
    return;
}
