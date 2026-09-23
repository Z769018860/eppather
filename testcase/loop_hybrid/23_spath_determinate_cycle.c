int main() {
    int state = 0;
    int i = 0;
    while (i < 4) {
        if (state >= 0) {
            state = 0 - state - 1;
        } else {
            state = 0 - state - 1;
        }
        i = i + 1;
    }
    return state;
}
