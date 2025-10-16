int func(int* pointer) {
    int v;
    v = *pointer;
    *pointer = 42;
    return;
}
