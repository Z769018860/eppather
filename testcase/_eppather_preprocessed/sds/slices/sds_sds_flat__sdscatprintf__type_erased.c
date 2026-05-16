/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdscatprintf slice=type_erased */


/* ===== TYPED APPROX FUNCTION sdscatprintf ===== */

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


