void insert(int anchor[2], int newlink[2]) {
    newlink[1] = anchor[1];
    newlink[0] = anchor[0];
    if (newlink[1] != 0) {
        int temp[2];
        temp[0] = newlink[1];
        temp[1] = *(int*)(newlink[1] + 4);
        temp[0] = newlink[0];
    }
    anchor[1] = newlink[0];
    return;
}
