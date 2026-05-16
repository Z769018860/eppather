/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdscmp slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION sdscmp ===== */

int *sdscmp(int *s1, int *s2)
{

    int l1;
    int l2;
    int minlen;
    int cmp;

    l1 = (s1[0]);
    l2 = (s2[0]);
    minlen = (l1 < l2) ? l1 : l2;
    cmp = (minlen);
    if (cmp == 0) return l1>l2? 1: (l1<l2? -1: 0);
    return cmp;
}


