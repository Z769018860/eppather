int say_number_rewritten(int s_len, int s_arr[5], int got_sign, int len, int n, int r, int has_lead, int i, int c[3], int depth) {
    {
        int i;
        for (i = 0; i < 5; i = i + 1) {
            if (s_arr[i] < 0 || s_arr[i] > 9) {
                return 0;
            }
        }
    }
    if (got_sign == -1) {
    }
    {
        int n1;
        n1 = len / 3;
        r = len % 3;
        if (r == 0) {
            n1 = n1 - 1;
            r = 3;
        }
        {
            int has_lead1;
            has_lead1 = 0;
            {
                int i;
                for (i = 0; i < 3; i = i + 1) {
                    if (s_len + (i - 3) >= 0) {
                        c[i] = s_arr[s_len + (i - 3)] - 0;
                    } else {
                        c[i] = 0;
                    }
                }
            }
            if (c[0] + c[1] + c[2] != 0) {
                if (c[0] != 0) {
                    has_lead1 = 1;
                }
                if (has_lead1 != 0 && (c[1] != 0 || c[2] != 0)) {
                }
                if (c[1] < 2) {
                    if (c[1] != 0 || c[2] != 0) {
                    }
                } else {
                    if (c[1] != 0) {
                        if (c[2] != 0) {
                        }
                    }
                    if (c[2] != 0) {
                    }
                }
            }
            if (has_lead1 != 0 && n1 != 0) {
                has_lead1 = 1;
                if (depth == 0) {
                } else {
                }
            }
        }
    }
    {
        int n2;
        n2 = len / 6;
        r = len % 6;
        if (r == 0) {
            r = 6;
            n2 = n2 - 1;
        }
        has_lead = 0;
        {
            int i;
            for (i = 0; i < n2; i = i + 1) {
            }
            if (n2 != 0) {
            }
        }
        n2 = n2 - 1;
        r = 6;
        {
            int i;
            for (i = 0; i < 5; i = i + 1) {
            }
        }
    }
    return 0;
}
