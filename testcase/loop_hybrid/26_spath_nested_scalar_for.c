int main(int seed) {
    int x = seed;
    for (int i = 0; i < 3; i = i + 1) {
        for (int j = 0; j < 2; j = j + 1) {
            x = x + 1;
        }
    }
    return x;
}
