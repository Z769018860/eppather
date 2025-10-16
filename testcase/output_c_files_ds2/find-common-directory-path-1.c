int common_len(const char *const *names, int n, char sep) {
    int pos[5];
    int i[5];
    pos[0] = 0;
    for (; ; pos[0] = pos[0] + 1) {
        for (i[0] = 0; i[0] < n; i[0] = i[0] + 1) {
            if (names[i[0]][pos[0]] != 0 && names[i[0]][pos[0]] == names[0][pos[0]]) {
                continue;
            }
            while (pos[0] > 0 && names[0][pos[0] = pos[0] - 1] != sep) {
                ;
            }
            return pos[0];
        }
    }
    return 0;
}
