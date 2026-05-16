/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsjoin slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION sdsjoin ===== */

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




/* ===== SEMANTIC STUBBED FUNCTION sdscat ===== */

int *sdscat(int *s, int *t)
{

    return sdscatlen(s, t, (t[0]));
}




/* ===== SEMANTIC STUBBED FUNCTION sdscatlen ===== */

int *sdscatlen(int *s, int *t, int len)
{
    int curlen;



    s = sdsMakeRoomFor(s,len);
    if (s == 0) return 0;
    (len);
    s[0] = curlen+len;
    s[curlen+len] = '\0';
    return s;
}




/* ===== SEMANTIC STUBBED FUNCTION sdsempty ===== */

int *sdsempty(void)
{

    return 1;
}


