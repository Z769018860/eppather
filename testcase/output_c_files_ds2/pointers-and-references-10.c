int addNodes(int array[5][5], int elems) {
    int temp[5][5];
    int i;
    int j;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            temp[i][j] = 0;
        }
    }
    for (i = 0; i < 5; i = i + 1) {
        if (i < elems) {
            for (j = 0; j < 5; j = j + 1) {
                array[i][j] = 0;
            }
            array[i][0] = i;
        }
    }
    return i;
}
