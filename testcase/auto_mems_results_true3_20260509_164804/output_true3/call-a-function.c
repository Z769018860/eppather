void f() {
    int x[5];
    x[0] = 0;
    return;
}

void g(int a, int b, int c) {
    int x[5];
    x[0] = a + b + c;
    return;
}

int op_arg(int a, int b, int c) {
    int x[5];
    x[0] = a;
    x[1] = b;
    x[2] = c;
    return x[0];
}

void h(int a, int b, int c, int d, int e, int f) {
    int x[5];
    x[0] = a;
    x[1] = b;
    x[2] = c;
    x[3] = d;
    x[4] = e;
    return;
}

void _v(int arg1, int arg2) {
    int x[5];
    x[0] = arg1;
    x[1] = arg2;
    return;
}
