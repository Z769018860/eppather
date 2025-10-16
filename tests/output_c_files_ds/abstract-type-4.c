int Silly_Instance(int arg1, int arg2) {
    int result;
    result = arg1 + arg2;
    return result;
}

int Abs_Method1(int obj, int arg) {
    int result;
    result = obj * arg;
    return result;
}

int Abs_Method2(int obj, int arg) {
    int result;
    result = obj + arg;
    return result;
}

void Abs_Method3(int obj, int arg) {
    int temp;
    temp = obj * arg;
    return;
}

void Abs_Free(int obj) {
    return;
}
