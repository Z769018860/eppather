int main() {
    int a[1];
    a[0] = 0;
    int i = 0;
    while (i < 4) {
        a[0] = a[0] + 1;
        i = i + 1;
    }
    return a[0];
}
