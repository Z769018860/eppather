int func() {
    int i;
    for (i = 1; i <= 105; i = i + 1) {
        if ((i % 3 != 0) && (i % 5 != 0)) {
            int temp = i;
        } else {
            if (i % 3 == 0) {
                char fizz[5] = {'F', 'i', 'z', 'z', '\0'};
            }
            if (i % 5 == 0) {
                char buzz[5] = {'B', 'u', 'z', 'z', '\0'};
            }
            if (i % 15 == 0) {
                char newline[2] = {'\n', '\0'};
            } else {
                char space[2] = {' ', '\0'};
            }
        }
    }
    return;
}
