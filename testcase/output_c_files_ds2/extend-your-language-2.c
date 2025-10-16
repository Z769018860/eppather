void if2_func(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9) {
    int i[5];
    int lval[5];
    int ep[5];
    int arg[5];
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (arg0 == 0) {
            if (arg1 == 0) {
                if (arg2 > 10) {
                    if (arg3 > 100) {
                        return;
                    } else {
                        return;
                    }
                } else {
                    if (arg4 > 100) {
                        return;
                    } else {
                        return;
                    }
                }
            } else {
                return;
            }
        } else {
            if (arg5 == 0) {
                if (arg6 > 10) {
                    if (arg7 > 100) {
                        return;
                    } else {
                        return;
                    }
                } else {
                    if (arg8 > 100) {
                        return;
                    } else {
                        return;
                    }
                }
            } else {
                return;
            }
        }
    }
    return;
}
