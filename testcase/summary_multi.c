int add_or_sub(int x, int y) {
    if (x > y) {
        return x + y;
    }
    return x - y;
}

int clamp_positive(int v) {
    if (v < 0) {
        return -v;
    }
    if (v > 10) {
        return 10;
    }
    return v;
}

int main() {
    int a = 5;
    int b = 3;
    int c = add_or_sub(a, b);
    int d = clamp_positive(c);
    if (d == 10) {
        return 1;
    }
    return 0;
}
