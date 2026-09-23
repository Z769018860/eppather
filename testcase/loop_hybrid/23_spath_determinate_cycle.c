int main(int x) {
    int i = 0;
    while (i < 4) {
        if (x < 0) {
            x = 1;
        } else {
            x = -1;
        }
        i = i + 1;
    }
    return x;
}
