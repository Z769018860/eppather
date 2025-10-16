void f() {
    return;
}

void g(int a, int b, int c) {
    int temp;
    temp = a + b + c;
    return;
}

int op_arg(int a, int b) {
    int c;
    c = (&b)[1];
    return a;
}

void h(int a) {
    int ap[5];
    ap[0] = a;
    return;
}

void _v(int arg1, int arg2) {
    int temp;
    temp = arg1 + arg2;
    return;
}
