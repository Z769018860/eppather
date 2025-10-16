void factor(int num, int fctrs_list[301], int fctrs_count[1], int flist[301], int flix[1]) {
    int dvsr;
    int ix;
    int ij;
    int newSize;
    flix[0] = 0;
    fctrs_count[0] = 0;
    for (dvsr = 1; dvsr * dvsr < num; dvsr = dvsr + 1) {
        if (num % dvsr != 0) {
            continue;
        }
        if (flix[0] == 300) {
            newSize = fctrs_count[0] + flix[0];
            for (ij = 0, ix = fctrs_count[0]; ix < newSize; ij = ij + 1, ix = ix + 1) {
                fctrs_list[ix] = flist[ij];
            }
            fctrs_count[0] = newSize;
            flix[0] = 0;
        }
        flist[flix[0]] = dvsr;
        flix[0] = flix[0] + 1;
        flist[flix[0]] = num / dvsr;
        flix[0] = flix[0] + 1;
    }
    if (dvsr * dvsr == num) {
        flist[flix[0]] = dvsr;
        flix[0] = flix[0] + 1;
    }
    if (flix[0] > 0) {
        newSize = fctrs_count[0] + flix[0];
        for (ij = 0, ix = fctrs_count[0]; ix < newSize; ij = ij + 1, ix = ix + 1) {
            fctrs_list[ix] = flist[ij];
        }
        fctrs_count[0] = newSize;
    }
    return;
}
