double functionA(double v) {
    return v * v * v;
}

double functionB(double v) {
    double result;
    int i;
    result = 1.0;
    for (i = 0; i < 3; i = i + 1) {
        result = result * v;
    }
    return result;
}

double Function1(double (*f2)(double), double val) {
    return f2(val);
}

double (*WhichFunc(int idx))(double) {
    if (idx < 4) {
        return &functionA;
    } else {
        return &functionB;
    }
}

double InvokeComposed(double (*f1)(double), double (*f2)(double), double val) {
    return f1(f2(val));
}

double CallComposed(double (*f1)(double), double (*f2)(double), double val) {
    return f1(f2(val));
}

double ComposeAndCall(int funcA_idx, int funcB_idx, double val) {
    double (*funcListA[4])(double) = {&functionA, 0, 0, 0};
    double (*funcListB[4])(double) = {&functionB, 0, 0, 0};
    return CallComposed(funcListA[funcA_idx], funcListB[funcB_idx], val);
}

return;
