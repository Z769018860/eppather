int pancake_sort(int list[9]) {
    int moves = 0;
    int i;
    int j;
    int max_index;
    int temp;
    for (i = 9; i > 1; i = i - 1) {
        max_index = 0;
        for (j = 0; j < i; j = j + 1) {
            if (list[j] > list[max_index]) {
                max_index = j;
            }
        }
        if (max_index != i - 1) {
            for (j = 0; j < (max_index + 1) / 2; j = j + 1) {
                temp = list[j];
                list[j] = list[max_index - j];
                list[max_index - j] = temp;
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
