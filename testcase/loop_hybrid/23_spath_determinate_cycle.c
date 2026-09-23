int main(int x) {
    for (int i = 0; i < 4; i = i + 1) {
        if (x < 1) {
            x = 2;
        } else {
            x = 0;
        }
    }
    return x;
}
