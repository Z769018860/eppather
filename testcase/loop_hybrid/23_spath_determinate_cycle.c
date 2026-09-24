int main() {
    int state = 0;
    int i = 0;
    while (i < 4) {
        if (state < 1) {
            state = 2;
        } else {
            state = 0;
        }
        i = i + 1;
    }
    return state;
}
