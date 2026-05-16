/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsjoin slice=type_erased */


/* ===== TYPED APPROX FUNCTION sdsjoin ===== */

int *sdsjoin(int *argv, int argc, int *sep)
{
    int join;


    int j;

    for (j = 0; j < argc; j++) {
        join = sdscat(join, argv[j]);
        if (j != argc-1) join = sdscat(join,sep);
    }
    return join;
}




/* ===== TYPED APPROX FUNCTION sdscat ===== */

int *sdscat(int *s, int *t)
{

    return sdscatlen(s, t, 1);
}




/* ===== TYPED APPROX FUNCTION sdscatlen ===== */

int *sdscatlen(int *s, int *t, int len)
{

    int curlen = 1;

    s = sdsMakeRoomFor(s,len);
    if (s == 0) return 0;
    1;
    sdssetlen(s, curlen+len);
    s[curlen+len] = '\0';
    return s;
}




/* ===== TYPED APPROX FUNCTION sdsempty ===== */

int *sdsempty(void)
{

    return 1;
}


