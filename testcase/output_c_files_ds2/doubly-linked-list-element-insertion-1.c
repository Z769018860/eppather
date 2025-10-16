void insert(int anchor[5], int newlink[5]) {
    int next[5];
    int prev[5];
    next[0] = anchor[1];
    prev[0] = anchor[0];
    newlink[1] = next[0];
    newlink[0] = prev[0];
    next[0] = newlink[0];
    anchor[1] = newlink[0];
    return;
}
