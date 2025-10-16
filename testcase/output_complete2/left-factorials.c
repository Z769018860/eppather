void mpz_left_fac_ui(int rop[5], int op)
{
    int t1[5];
    t1[0] = 1;
    rop[0] = 0;

    int i;
    for (i = 1; i <= op; i = i + 1) {
        rop[0] = rop[0] + t1[0];
        t1[0] = t1[0] * i;
    }

    return;
}

void mpz_digitcount(int op[5])
{
    int t[5];
    t[0] = 0;
    int ret[5];
    ret[0] = 0;

    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (op[i] != 0) {
            ret[0] = ret[0] + 1;
        }
    }

    return;
}

void combined_function(int rop[5], int op)
{
    int t1[5];
    t1[0] = 1;
    rop[0] = 0;

    int i;
    for (i = 1; i <= op; i = i + 1) {
        rop[0] = rop[0] + t1[0];
        t1[0] = t1[0] * i;
    }

    int t[5];
    t[0] = 0;
    int ret[5];
    ret[0] = 0;

    for (i = 0; i < 5; i = i + 1) {
        if (rop[i] != 0) {
            ret[0] = ret[0] + 1;
        }
    }

    return;
}
