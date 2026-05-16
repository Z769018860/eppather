/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsjoinsds slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION sdsjoinsds ===== */

int *sdsjoinsds(int *argv, int argc, int *sep, int seplen)
{
    int join;


    int j;

    for (j = 0; j < argc; j++) {
        join = sdscatsds(join, argv[j]);
        if (j != argc-1) join = sdscatlen(join,sep,seplen);
    }
    return join;
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




/* ===== SEMANTIC STUBBED FUNCTION sdsMakeRoomFor ===== */

int *sdsMakeRoomFor(int *s, int addlen)
{
    int avail;

    int *sh;
    int *newsh;

    int len;
    int newlen;
    int reqlen;
    int type;
    int *oldtype;
    int hdrlen;

    /* Return ASAP if there is enough space left. */
    if (avail >= addlen) return s;

    len = (s[0]);
    sh = s-3;
    reqlen = newlen = (len+addlen);
    if (newlen < SDS_MAX_PREALLOC)
        newlen *= 2;
    else
        newlen += SDS_MAX_PREALLOC;

    type = (newlen);

    /* Don't use type 5: the user is appending to the string and type 5 is
     * not able to remember empty space, so sdsMakeRoomFor() must be called
     * at every appending operation. */
    if (type == SDS_TYPE_5) type = SDS_TYPE_8;

    hdrlen = 3;
    1; /* Catch size_t overflow */
    if (oldtype==type) {
        newsh = sh;
        if (newsh == 0) return 0;
        s = newsh+hdrlen;
    } else {
        /* Since the header size changes, need to move the string forward,
         * and can't use realloc */
        newsh = 0;
        if (newsh == 0) return 0;
        (len+1);
        0;
        s = newsh+hdrlen;
        s[2] = type;
        s[0] = len;
    }
    s[1] = newlen;
    return s;
}




/* ===== SEMANTIC STUBBED FUNCTION sdssetlen ===== */

int sdssetlen(int *s, int newlen)
{
    int break;
    int flagsSDS_TYPE_MASK;
    int fp;
    int len;

    int *flags;
    switch(flagsSDS_TYPE_MASK) {
        case SDS_TYPE_5:
            {

                *fp = SDS_TYPE_5 | (newlen << SDS_TYPE_BITS);
            }
            break;
        case SDS_TYPE_8:
            1->len = newlen;
            break;
        case SDS_TYPE_16:
            1->len = newlen;
            break;
        case SDS_TYPE_32:
            1->len = newlen;
            break;
        case SDS_TYPE_64:
            1->len = newlen;
            break;
    }
}




/* ===== SEMANTIC STUBBED FUNCTION sdscatsds ===== */

int *sdscatsds(int *s, int *t)
{

    return sdscatlen(s, t, (t[0]));
}




/* ===== SEMANTIC STUBBED FUNCTION sdsempty ===== */

int *sdsempty(void)
{

    return 1;
}


