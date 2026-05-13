void init(int t[5], int x[5]) {
    t[0] = 0;
    x[0] = 0;
}

int square(int env[5], int x[5]) {
    int xbind[5];
    int xval[5];
    int result[5];
    xbind[0] = env[0];
    xval[0] = env[1];
    result[0] = xval[0] * xval[0];
    return result[0];
}

void func(int t[5], int x[5], int funlist[5], int iter[5]) {
    init(t, x);
    int i;
    int closure_env[5];
    int temp[5];
    
    for (i = 0; i < 5; i = i + 1) {
        closure_env[0] = x[0];
        closure_env[1] = i;
        funlist[0] = closure_env[0];
        funlist[1] = closure_env[1];
    }
    
    for (iter[0] = funlist[0]; iter[0] != 0; iter[0] = funlist[1]) {
        int fun[5];
        int square_val[5];
        fun[0] = iter[0];
        square_val[0] = square(fun, x);
    }
    return;
}
