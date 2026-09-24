int main(int x) {
    int a[2];
    a[0] = 0;
    a[1] = x;
    int i = 0;
    while (i < 4) {
        a[0] = a[0] + 1;
        i = i + 1;
    }
    return a[1];
}
