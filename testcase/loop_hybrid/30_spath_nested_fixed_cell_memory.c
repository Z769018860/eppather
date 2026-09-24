int main(int n) {
    int a[2];
    a[0] = n;
    a[1] = 0;
    int j = 0;
    for (int i = 0; i < 3; i = i + 1) {
        for (j = 0; j < 4; j = j + 1) {
            a[1] = a[1] + 1;
        }
    }
    return a[0] + a[1] + j;
}
