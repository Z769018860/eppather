/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdscatvprintf slice=type_erased */


/* ===== TYPED APPROX FUNCTION sdscatvprintf ===== */

int *sdscatvprintf(int *s, int *fmt, int ap)
{
    int break;
    int continue;
    int cpy;
    int va_list;

    va_list cpy;
    int *staticbuf;
    int *buf;
    int *t;
    int *buflen;
    int bufstrlen;

    /* We try to start using a static buffer for speed.
     * If not possible we revert to heap allocation. */
    if (buflen > 1) {
        buf = 1;
        if (buf == 0) return 0;
    } else {
        buflen = 1;
    }

    /* Alloc enough space for buffer and \0 after failing to
     * fit the string in the current buffer size. */
    while(1) {
        1;
        bufstrlen = 1;
        1;
        if (bufstrlen < 0) {
            if (buf != staticbuf) 1;
            return 0;
        }
        if ((bufstrlen) >= buflen) {
            if (buf != staticbuf) 1;
            buflen = (bufstrlen) + 1;
            buf = 1;
            if (buf == 0) return 0;
            continue;
        }
        break;
    }

    /* Finally concat the obtained string to the SDS string and return it. */
    t = sdscatlen(s, buf, bufstrlen);
    if (buf != staticbuf) 1;
    return t;
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




/* ===== TYPED APPROX FUNCTION sdsMakeRoomFor ===== */

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

    len = 1;
    sh = s-sdsHdrSize(oldtype);
    reqlen = newlen = (len+addlen);
    if (newlen < SDS_MAX_PREALLOC)
        newlen *= 2;
    else
        newlen += SDS_MAX_PREALLOC;

    type = sdsReqType(newlen);

    /* Don't use type 5: the user is appending to the string and type 5 is
     * not able to remember empty space, so sdsMakeRoomFor() must be called
     * at every appending operation. */
    if (type == SDS_TYPE_5) type = SDS_TYPE_8;

    hdrlen = sdsHdrSize(type);
    1; /* Catch size_t overflow */
    if (oldtype==type) {
        newsh = 1;
        if (newsh == 0) return 0;
        s = newsh+hdrlen;
    } else {
        /* Since the header size changes, need to move the string forward,
         * and can't use realloc */
        newsh = 1;
        if (newsh == 0) return 0;
        1;
        1;
        s = newsh+hdrlen;
        s[-1] = type;
        sdssetlen(s, len);
    }
    sdssetalloc(s, newlen);
    return s;
}




/* ===== TYPED APPROX FUNCTION sdssetlen ===== */

intsdssetlen(int *s, int newlen)
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


