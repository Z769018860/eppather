int addNodes(int array[10][1], int elems) {
    int i;
    for (i = 0; i < elems; i = i + 1) {
        if (i >= 10) {
            break;
        }
        array[i][0] = i;
    }
    return i;
    return;
}
