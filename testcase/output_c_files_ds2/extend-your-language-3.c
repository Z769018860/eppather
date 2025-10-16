void check_numbers(int argc, char* argv[]) {
    int i;
    int j;
    int is_num;
    int num;
    int len;
    int c;
    for (i = 1; i < argc; i = i + 1) {
        is_num = 1;
        num = 0;
        len = 0;
        for (j = 0; argv[i][j] != 0; j = j + 1) {
            len = len + 1;
        }
        if (len == 0) {
            is_num = 0;
        } else {
            j = 0;
            if (argv[i][0] == '-') {
                j = j + 1;
            }
            for (; j < len; j = j + 1) {
                c = argv[i][j];
                if (c < '0' || c > '9') {
                    is_num = 0;
                    break;
                }
            }
        }
        if (is_num) {
            num = 0;
            j = 0;
            if (argv[i][0] == '-') {
                j = j + 1;
            }
            for (; j < len; j = j + 1) {
                num = num * 10 + (argv[i][j] - '0');
            }
            if (argv[i][0] == '-') {
                num = -num;
            }
            if (num > 99) {
            } else if (num > 9) {
            } else {
            }
        } else {
        }
    }
    return;
}
