int pancake_sort(int list[9], int n, int verbose) {
    int i;
    int j;
    int max;
    int moves = 0;
    int temp;
    for (i = n; i > 1; i = i - 1) {
        max = 0;
        for (j = 0; j < i; j = j + 1) {
            if (list[j] > list[max]) {
                max = j;
            }
        }
        if (max != i - 1) {
            for (j = 0; j < (max + 1) / 2; j = j + 1) {
                temp = list[j];
                list[j] = list[max - j];
                list[max - j] = temp;
            }
            for (j = 0; j < i / 2; j = j + 1) {
                temp = list[j];
                list[j] = list[i - 1 - j];
                list[i - 1 - j] = temp;
            }
            moves = moves + 1;
        }
    }
    return moves;
}
