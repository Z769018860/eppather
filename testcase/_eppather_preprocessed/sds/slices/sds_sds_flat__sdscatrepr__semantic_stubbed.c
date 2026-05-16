/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdscatrepr slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION sdscatrepr ===== */

int *sdscatrepr(int *s, int *p, int len)
{

    s = sdscatlen(s,0,1);
    while(len--) {
        switch(*p) {
        case '\\':
        case '0\\%c0\\n0\\r0\\t0\\a0\\b0%c0\\x%02x0\0,1);
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




/* ===== SEMANTIC STUBBED FUNCTION sdscatprintf ===== */

int *sdscatprintf(int *s, int *fmt, int arg2)
{
    int ap;
    int va_list;

    va_list ap;
    int *t;
    1;
    t = sdscatvprintf(s,fmt,ap);
    1;
    return t;
}




/* ===== SEMANTIC STUBBED FUNCTION sdscatvprintf ===== */

int *sdscatvprintf(int *s, int *fmt, int ap)
{
    int break;
    int buflen;
    int continue;
    int cpy;
    int va_list;

    va_list cpy;
    int *staticbuf;
    int *buf;
    int *t;

    int bufstrlen;

    /* We try to start using a static buffer for speed.
     * If not possible we revert to heap allocation. */
    if (buflen > 1) {
        buf = 0;
        if (buf == 0) return 0;
    } else {
        buflen = 1;
    }

    /* Alloc enough space for buffer and \0 after failing to
     * fit the string in the current buffer size. */
    while(1) {
        1;
        bufstrlen = (buflen);
        1;
        if (bufstrlen < 0) {
            if (buf != staticbuf) 0;
            return 0;
        }
        if ((bufstrlen) >= buflen) {
            if (buf != staticbuf) 0;
            buflen = (bufstrlen) + 1;
            buf = 0;
            if (buf == 0) return 0;
            continue;
        }
        break;
    }

    /* Finally concat the obtained string to the SDS string and return it. */
    t = sdscatlen(s, buf, bufstrlen);
    if (buf != staticbuf) 0;
    return t;
}


