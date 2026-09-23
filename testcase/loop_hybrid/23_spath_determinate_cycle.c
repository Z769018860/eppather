int main() {
    int x = 0;
    int i = 0;
    while (i < 4) {
        if (x < 1) {
            x = 2;
        } else {
            x = 0;
        }
        i = i + 1;
    }
    return x;
}
