int func(int* pointer, int v) {
    v = *(pointer + 3);
    v = *(pointer - 1);
    v = *(pointer + 3);
    v = *(pointer - 1);
    return;
}
