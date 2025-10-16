void radix_sort(int a[16])
{
    unsigned x[16];
    int i;
    for (i = 0; i < 16; i = i + 1) {
        x[i] = (unsigned)a[i] ^ 0x80000000;
    }

    {
        unsigned bit = 0x80000000;
        unsigned from[16];
        for (i = 0; i < 16; i = i + 1) {
            from[i] = x[i];
        }
        {
            unsigned ll[16];
            unsigned rr[16];
            int ll_idx = 0;
            int rr_idx = 15;
            for (;;) {
                while (ll_idx < rr_idx && !(from[ll_idx] & bit)) {
                    ll_idx = ll_idx + 1;
                }
                while (ll_idx < rr_idx && (from[rr_idx] & bit)) {
                    rr_idx = rr_idx - 1;
                }
                if (ll_idx >= rr_idx) {
                    break;
                }
                {
                    unsigned tmp = from[ll_idx];
                    from[ll_idx] = from[rr_idx];
                    from[rr_idx] = tmp;
                }
                ll_idx = ll_idx + 1;
                rr_idx = rr_idx - 1;
            }
            if (!(from[ll_idx] & bit) && ll_idx < 16) {
                ll_idx = ll_idx + 1;
            }
            bit = bit >> 1;
            {
                unsigned part1[16];
                unsigned part2[16];
                int j;
                for (j = 0; j < ll_idx; j = j + 1) {
                    part1[j] = from[j];
                }
                for (j = ll_idx; j < 16; j = j + 1) {
                    part2[j - ll_idx] = from[j];
                }
                {
                    unsigned bit1 = bit;
                    unsigned ll1[16];
                    unsigned rr1[16];
                    int ll_idx1 = 0;
                    int rr_idx1 = ll_idx - 1;
                    for (;;) {
                        while (ll_idx1 < rr_idx1 && !(part1[ll_idx1] & bit1)) {
                            ll_idx1 = ll_idx1 + 1;
                        }
                        while (ll_idx1 < rr_idx1 && (part1[rr_idx1] & bit1)) {
                            rr_idx1 = rr_idx1 - 1;
                        }
                        if (ll_idx1 >= rr_idx1) {
                            break;
                        }
                        {
                            unsigned tmp = part1[ll_idx1];
                            part1[ll_idx1] = part1[rr_idx1];
                            part1[rr_idx1] = tmp;
                        }
                        ll_idx1 = ll_idx1 + 1;
                        rr_idx1 = rr_idx1 - 1;
                    }
                    if (!(part1[ll_idx1] & bit1) && ll_idx1 < ll_idx) {
                        ll_idx1 = ll_idx1 + 1;
                    }
                }
                {
                    unsigned bit2 = bit;
                    unsigned ll2[16];
                    unsigned rr2[16];
                    int ll_idx2 = 0;
                    int rr_idx2 = 15 - ll_idx;
                    for (;;) {
                        while (ll_idx2 < rr_idx2 && !(part2[ll_idx2] & bit2)) {
                            ll_idx2 = ll_idx2 + 1;
                        }
                        while (ll_idx2 < rr_idx2 && (part2[rr_idx2] & bit2)) {
                            rr_idx2 = rr_idx2 - 1;
                        }
                        if (ll_idx2 >= rr_idx2) {
                            break;
                        }
                        {
                            unsigned tmp = part2[ll_idx2];
                            part2[ll_idx2] = part2[rr_idx2];
                            part2[rr_idx2] = tmp;
                        }
                        ll_idx2 = ll_idx2 + 1;
                        rr_idx2 = rr_idx2 - 1;
                    }
                    if (!(part2[ll_idx2] & bit2) && ll_idx2 < 16 - ll_idx) {
                        ll_idx2 = ll_idx2 + 1;
                    }
                }
                for (j = 0; j < ll_idx; j = j + 1) {
                    from[j] = part1[j];
                }
                for (j = ll_idx; j < 16; j = j + 1) {
                    from[j] = part2[j - ll_idx];
                }
            }
        }
        for (i = 0; i < 16; i = i + 1) {
            x[i] = from[i];
        }
    }

    for (i = 0; i < 16; i = i + 1) {
        a[i] = (int)(x[i] ^ 0x80000000);
    }
    return;
}
