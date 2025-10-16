int foo[2];
int new_times[2][2];

void rewrite_function() {
    for (int i = 0; i < 2; i = i + 1) {
        new_times[0][i] = foo[i];
    }
    for (int j = 0; j < 2; j = j + 1) {
        new_times[1][j] = 0;
    }
    return;
}
