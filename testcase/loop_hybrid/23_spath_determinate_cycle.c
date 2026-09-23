int main() {
    int x = 0;
    for (int i = 0; i < 4; i = i + 1) {
        if (x < 1) {
            x = 2;
        } else {
            x = 0;
        }
    }
    return x;
}
