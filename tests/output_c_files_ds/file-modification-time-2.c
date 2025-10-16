int foo[10];
int new_times[2][2];

void func() {
    for (int i = 0; i < 10; i = i + 1) {
        foo[i] = 0;
    }
    for (int i = 0; i < 2; i = i + 1) {
        for (int j = 0; j < 2; j = j + 1) {
            new_times[i][j] = 0;
        }
    }
    return;
}
