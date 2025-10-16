int* funcPointer_helper(long* parameter) {
    int* result = 0;
    return result;
}

int* myFuncComplex(double* (*paramFunc)(long*)) {
    int* result = 0;
    return result;
}

void funcPointer_assign() {
    int* (*funcPointer)(double* (*)(long*)) = &myFuncComplex;
    return;
}
