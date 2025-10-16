int str_empty_test(int str_len) {
    int str[5];
    str[0] = 0;
    if (str) {
        if (str[0] == 0) {
            int i;
            int len = 0;
            for (i = 0; i < 5; i = i + 1) {
                if (str[i] != 0) {
                    len = len + 1;
                }
            }
            if (len == 0) {
                int cmp = 1;
                for (i = 0; i < 5; i = i + 1) {
                    if (str[i] != 0) {
                        cmp = 0;
                    }
                }
                if (cmp == 1) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
