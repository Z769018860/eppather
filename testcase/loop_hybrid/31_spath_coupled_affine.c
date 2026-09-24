int main(int n) {
    int x = n;
    int y = 0;
    int i = 0;
    while (i < 4) {
        x = x + y;
        y = y + 1;
        i = i + 1;
    }
    return x + y;
}
