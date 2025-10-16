int func(int n1, int n2) {
    int i[5];
    int j[5];
    for (j[0] = 1; j[0] < n1; j[0] = j[0] + 1) {
        for (i[0] = 0; i[0] < j[0]; i[0] = i[0] + 1) {
            if (n2 != 0) {
                return;
            }
        }
    }
    return;
}
