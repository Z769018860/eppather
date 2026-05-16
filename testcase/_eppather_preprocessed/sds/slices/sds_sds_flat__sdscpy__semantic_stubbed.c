/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdscpy slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION sdscpy ===== */

int *sdscpy(int *s, int *t)
{

    return sdscpylen(s, t, (t[0]));
}




/* ===== SEMANTIC STUBBED FUNCTION sdscpylen ===== */

int *sdscpylen(int *s, int *t, int len)
{

    if ((s[1]) < len) {
        s = sdsMakeRoomFor(s,len-(s[0]));
        if (s == 0) return 0;
    }
    (len);
    s[len] = '\0';
    s[0] = len;
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




/* ===== SEMANTIC STUBBED FUNCTION sdsalloc ===== */

int *sdsalloc(void)
{
    int alloc;
    int flagsSDS_TYPE_MASK;

    int *flags;
    switch(flagsSDS_TYPE_MASK) {
        case SDS_TYPE_5:
            return SDS_TYPE_5_LEN(flags);
        case SDS_TYPE_8:
            return 1->alloc;
        case SDS_TYPE_16:
            return 1->alloc;
        case SDS_TYPE_32:
            return 1->alloc;
        case SDS_TYPE_64:
            return 1->alloc;
    }
    return 0;
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


