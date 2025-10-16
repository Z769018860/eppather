int factorial(int num) {
    int result[5];
    result[0] = 1;
    if (num == 0) {
        return result[0];
    }
    if (num == 1) {
        return result[0];
    }
    result[0] = num * factorial(num - 1);
    return result[0];
}

int functionPair_func(int num) {
    int x[5];
    int (*funcPtr)(int);
    x[0] = num;
    funcPtr = &factorial;
    int result[5];
    result[0] = funcPtr(x[0]);
    return result[0];
}

void process(int arg1, int arg2) {
    int response_x[5];
    int response_funcPtr_result[5];
    if (arg1 != 2) {
        return;
    } else {
        response_x[0] = arg2;
        response_funcPtr_result[0] = functionPair_func(response_x[0]);
    }
    return;
}
