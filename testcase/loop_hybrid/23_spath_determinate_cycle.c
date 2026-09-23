int main(int x) {
    for (int i = 0; i < 4; i = i + 1) {
        if (x < 0) {
            x = 1;
        } else {
            x = -1;
        }
    }
    return x;
}
