int call_foo(int env[5]) {
    int result[5];
    result[0] = 0;
    if (result[0] == 0) {
        env[0] = 1;
        return;
    }
    if (result[0] == 1) {
        return;
    }
    return;
}
