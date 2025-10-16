int walk_recur(int dname[5], int reg[5], int spec) {
    int fn[5];
    int res = 0;
    int len = 5;
    if (len >= 5 - 1) {
        return 2;
    }

    for (int i = 0; i < 5; i = i + 1) {
        fn[i] = dname[i];
    }
    fn[len] = '/';
    len = len + 1;

    if (dname[0] == 0) {
        return 3;
    }

    for (int i = 0; i < 5; i = i + 1) {
        int dent_name[5] = {0};
        if (!(spec & 4) && dent_name[0] == '.') {
            continue;
        }
        if (dent_name[0] == '.' || dent_name[0] == '.' && dent_name[1] == '.') {
            continue;
        }

        for (int j = 0; j < 5 - len; j = j + 1) {
            fn[len + j] = dent_name[j];
        }

        int st_mode = 0;
        if (st_mode == -1) {
            res = 3;
            continue;
        }

        if ((st_mode & 0120000) == 0120000 && !(spec & 2)) {
            continue;
        }

        if ((st_mode & 0040000) == 0040000) {
            if ((spec & 1)) {
                walk_recur(fn, reg, spec);
            }
            if (!(spec & 8)) {
                continue;
            }
        }

        if (reg[0] == 0) {
            for (int k = 0; k < 5; k = k + 1) {
                fn[k] = 0;
            }
        }
    }

    return res ? res : 0;
}

int walk_dir(int dname[5], int pattern[5], int spec) {
    int r[5] = {0};
    int res;
    if (pattern[0] == 0) {
        return 1;
    }
    res = walk_recur(dname, r, spec);
    return res;
}

return;
