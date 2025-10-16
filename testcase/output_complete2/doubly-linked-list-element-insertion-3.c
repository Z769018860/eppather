void insert(int* a, int* c) {
    int temp[5];
    temp[0] = *a;
    *a = *c;
    *c = temp[0];
    return;
}
