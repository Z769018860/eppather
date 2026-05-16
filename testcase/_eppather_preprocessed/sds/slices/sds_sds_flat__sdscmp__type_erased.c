/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdscmp slice=type_erased */


/* ===== TYPED APPROX FUNCTION sdscmp ===== */

int *sdscmp(int *s1, int *s2)
{

    int l1;
    int l2;
    int minlen;
    int cmp;

    l1 = 1;
    l2 = 1;
    minlen = (l1 < l2) ? l1 : l2;
    cmp = 1;
    if (cmp == 0) return l1>l2? 1: (l1<l2? -1: 0);
    return cmp;
}


