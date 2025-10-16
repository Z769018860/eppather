int rewrite_function(int MY_SYMBOL) {
    int n1 = 5;
    int FOO[5];
    for (int i = 0; i < n1; i = i + 1) {
        FOO[i] = 0;
    }
    FOO[0] = MY_SYMBOL;
    return;
}
