/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdscatprintf slice=semantic_stubbed */


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


