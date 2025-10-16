void median(int list[5], int size) {
    int i;
    int j;
    int temp;
    for (i = 0; i < size; i = i + 1) {
        for (j = i + 1; j < size; j = j + 1) {
            if (list[i] > list[j]) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    return;
}
