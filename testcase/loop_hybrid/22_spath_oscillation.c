int main(int x) {
    int i = 0;
    int total = 0;
    while (i < 4) {
        if (x > 0) {
            x = x - 1;
        } else {
            x = x + 1;
        }
        total = total + x;
        i = i + 1;
    }
    return total;
}
