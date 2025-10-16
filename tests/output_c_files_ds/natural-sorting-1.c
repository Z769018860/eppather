int w_numcmp(const wchar_t* pa, const wchar_t* pb) {
    int sa;
    int sb;
    int ea;
    int eb;
    while (*pa && *pb) {
        if (iswdigit(*pa) && iswdigit(*pb)) {
            sa = 0;
            sb = 0;
            while (pa[sa] == L'0') {
                sa = sa + 1;
            }
            while (pb[sb] == L'0') {
                sb = sb + 1;
            }
            ea = sa;
            eb = sb;
            while (iswdigit(pa[ea])) {
                ea = ea + 1;
            }
            while (iswdigit(pb[eb])) {
                eb = eb + 1;
            }
            if (eb - sb > ea - sa) {
                return -1;
            }
            if (eb - sb < ea - sa) {
                return 1;
            }
            while (sb < eb) {
                if (pa[sa] > pb[sb]) {
                    return 1;
                }
                if (pa[sa] < pb[sb]) {
                    return -1;
                }
                sa = sa + 1;
                sb = sb + 1;
            }
            pa = pa + ea;
            pb = pb + eb;
        }
        else if (iswdigit(*pa)) {
            return 1;
        }
        else if (iswdigit(*pb)) {
            return -1;
        }
        else {
            if (*pa > *pb) {
                return 1;
            }
            if (*pa < *pb) {
                return -1;
            }
            pa = pa + 1;
            pb = pb + 1;
        }
    }
    return (!*pa && !*pb) ? 0 : *pa ?  1 : -1;
}

int w_cmp(const wchar_t* pa, const wchar_t* pb) {
    while (*pa && *pb) {
        if (*pa > *pb) {
            return 1;
        }
        if (*pa < *pb) {
            return -1;
        }
        pa = pa + 1;
        pb = pb + 1;
    }
    return (!*pa && !*pb) ? 0 : *pa ?  1 : -1;
}

void natural_sort(wchar_t* strings[7], int flags) {
    wchar_t* temp;
    int i;
    int j;
    for (i = 0; i < 7; i = i + 1) {
        for (j = i + 1; j < 7; j = j + 1) {
            if ((flags & 32) ? w_numcmp(strings[i], strings[j]) > 0 : w_cmp(strings[i], strings[j]) > 0) {
                temp = strings[i];
                strings[i] = strings[j];
                strings[j] = temp;
            }
        }
    }
    return;
}
