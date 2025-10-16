int inv(int a) {
    return a ^ -1;
}

void zeckendorf_operations(int self_dVal, int self_dLen, int rhs_dVal, int rhs_dLen, int operation, int *result_dVal, int *result_dLen) {
    void a(int *dVal, int *dLen, int n) {
        int i = n;
        for (;;) {
            if (*dLen < i) {
                *dLen = i;
            }
            int j = (*dVal >> (i * 2)) & 3;
            if (j == 0 || j == 1) {
                return;
            }
            if (j == 2) {
                if (((*dVal >> ((i + 1) * 2)) & 1) != 1) {
                    return;
                }
                *dVal = *dVal + (1 << (i * 2 + 1));
                return;
            }
            if (j == 3) {
                *dVal = *dVal & inv(3 << (i * 2));
                int temp_dVal = *dVal;
                int temp_dLen = *dLen;
                b(&temp_dVal, &temp_dLen, (i + 1) * 2);
                *dVal = temp_dVal;
                *dLen = temp_dLen;
            }
            i = i + 1;
        }
    }

    void b(int *dVal, int *dLen, int pos) {
        if (pos == 0) {
            *dVal = *dVal + 1;
            a(dVal, dLen, 0);
            return;
        }
        if (((*dVal >> pos) & 1) == 0) {
            *dVal = *dVal + (1 << pos);
            a(dVal, dLen, pos / 2);
            if (pos > 1) {
                a(dVal, dLen, pos / 2 - 1);
            }
        } else {
            *dVal = *dVal & inv(1 << pos);
            b(dVal, dLen, pos + 1);
            if (pos > 1) {
                b(dVal, dLen, pos - 2);
            } else {
                b(dVal, dLen, pos - 1);
            }
        }
    }

    void c(int *dVal, int *dLen, int pos) {
        if (((*dVal >> pos) & 1) == 1) {
            *dVal = *dVal & inv(1 << pos);
            return;
        }
        c(dVal, dLen, pos + 1);
        if (pos > 0) {
            b(dVal, dLen, pos - 1);
        } else {
            *dVal = *dVal + 1;
            a(dVal, dLen, 0);
        }
    }

    void addAssign(int *dVal, int *dLen, int rhs_dVal, int rhs_dLen) {
        int gn;
        for (gn = 0; gn < (rhs_dLen + 1) * 2; gn = gn + 1) {
            if (((rhs_dVal >> gn) & 1) == 1) {
                b(dVal, dLen, gn);
            }
        }
    }

    void subAssign(int *dVal, int *dLen, int rhs_dVal, int rhs_dLen) {
        int gn;
        for (gn = 0; gn < (rhs_dLen + 1) * 2; gn = gn + 1) {
            if (((rhs_dVal >> gn) & 1) == 1) {
                c(dVal, dLen, gn);
            }
        }
        while ((((*dVal >> (*dLen * 2)) & 3) == 0) || (*dLen == 0)) {
            *dLen = *dLen - 1;
        }
    }

    void mulAssign(int *dVal, int *dLen, int rhs_dVal, int rhs_dLen) {
        int na_dVal = rhs_dVal;
        int na_dLen = rhs_dLen;
        int nb_dVal = rhs_dVal;
        int nb_dLen = rhs_dLen;
        int nr_dVal = 0;
        int nr_dLen = 0;
        int nt_dVal;
        int nt_dLen;
        int i;

        for (i = 0; i < (*dLen + 1) * 2; i = i + 1) {
            if (((*dVal >> i) & 1) > 0) {
                addAssign(&nr_dVal, &nr_dLen, nb_dVal, nb_dLen);
            }
            nt_dVal = nb_dVal;
            nt_dLen = nb_dLen;
            addAssign(&nb_dVal, &nb_dLen, na_dVal, na_dLen);
            na_dVal = nt_dVal;
            na_dLen = nt_dLen;
        }

        *dVal = nr_dVal;
        *dLen = nr_dLen;
    }

    *result_dVal = self_dVal;
    *result_dLen = self_dLen;

    if (operation == 0) {
        addAssign(result_dVal, result_dLen, rhs_dVal, rhs_dLen);
    } else if (operation == 1) {
        subAssign(result_dVal, result_dLen, rhs_dVal, rhs_dLen);
    } else if (operation == 2) {
        mulAssign(result_dVal, result_dLen, rhs_dVal, rhs_dLen);
    }

    return;
}
