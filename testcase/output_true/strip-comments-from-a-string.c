void process_string(int ch, int str[100], int i) {
    for (i = 0; i < 100; i = i + 1) {
        if (str[i] == 0) {
            break;
        }
        if (str[i] == 35 || str[i] == 59) {
            str[i] = 0;
            break;
        }
    }
    for (i = 0; i < 5; i = i + 1) {
        if (ch == 121 || ch == 89) {
            for (i = 0; i < 100; i = i + 1) {
                str[i] = 0;
            }
        }
    }
    return;
}
