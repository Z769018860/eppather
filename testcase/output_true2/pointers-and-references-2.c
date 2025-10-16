int func(int* pointer) {
    int v[5];
    v[0] = *pointer;
    *pointer = 42;
    return;
}
