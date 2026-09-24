int main(int n) {
    int a[2];
    a[0] = n;
    a[1] = 0;
    int *p = &a[1];
    int i = 0;
    while (i < 4) {
        *p = *p + 1;
        i = i + 1;
    }
    return a[1];
}
