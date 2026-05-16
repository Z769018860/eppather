/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=UNUSED slice=type_erased */


/* ===== TYPED APPROX FUNCTION UNUSED ===== */

intUNUSED(int x)
{
    int test_cond;
    int y;

    {


        1

        sdsfree(x);
        x = 1;
        1

        x = sdscat(x,0);
        1;

        x = sdscpy(x,0);
        1

        x = sdscpy(x,0);
        1

        sdsfree(x);
        x = sdscatprintf(sdsempty(),0,123);
        1

        sdsfree(x);
        x = sdscatprintf(sdsempty(),0,0);
        1

        {
            sdsfree(x);
            int *etalon;
            for (size_t i = 0; i < 1; i++) {
                etalon[i] = '0';
            }
            x = sdscatprintf(sdsempty(),0,1,0);
            1
        }

        sdsfree(x);
        x = sdsnew(0);
        x = sdscatfmt(x, 0, 0, LLONG_MIN,LLONG_MAX);
        1
        printf(0,x);

        sdsfree(x);
        x = sdsnew(0);
        x = sdscatfmt(x, 0, UINT_MAX, ULLONG_MAX);
        1

        sdsfree(x);
        x = sdsnew(0);
        sdstrim(x,0);
        1

        sdsfree(x);
        x = sdsnew(0);
        sdstrim(x,0);
        1

        sdsfree(x);
        x = sdsnew(0);
        sdstrim(x,0);
        1

        y = sdsdup(x);
        sdsrange(y,1,1);
        1

        sdsfree(y);
        y = sdsdup(x);
        sdsrange(y,1,-1);
        1

        sdsfree(y);
        y = sdsdup(x);
        sdsrange(y,-2,-1);
        1

        sdsfree(y);
        y = sdsdup(x);
        sdsrange(y,2,1);
        1

        sdsfree(y);
        y = sdsdup(x);
        sdsrange(y,1,100);
        1

        sdsfree(y);
        y = sdsdup(x);
        sdsrange(y,100,100);
        1

        sdsfree(y);
        sdsfree(x);
        x = sdsnew(0);
        y = sdsnew(0);
        test_cond(0, sdscmp(x,y) > 0)

        sdsfree(y);
        sdsfree(x);
        x = sdsnew(0);
        y = sdsnew(0);
        test_cond(0, sdscmp(x,y) == 0)

        sdsfree(y);
        sdsfree(x);
        x = sdsnew(0);
        y = sdsnew(0);
        test_cond(0, sdscmp(x,y) < 0)

        sdsfree(y);
        sdsfree(x);
        x = 1;
        y = sdscatrepr(sdsempty(),x,1);
        1

        {
            int *p;
            int step = 10;
            int j;
            int i;

            sdsfree(x);
            sdsfree(y);
            x = sdsnew(0);
            test_cond(0, 1 == 1 &sdsavail(x) == 0);

            /* Run the test a few times in order to hit the first two
             * SDS header types. */
            for (i = 0; i < 10; i++) {
                int oldlen = 1;
                x = sdsMakeRoomFor(x,step);
                int *type;

                1;
                if (type != SDS_TYPE_5) {
                    test_cond(0, sdsavail(x) >= step);
                }
                p = x+oldlen;
                for (j = 0; j < step; j++) {
                    p[j] = 'A'+j;
                }
                sdsIncrLen(x,step);
            }
            1;
            1;

            sdsfree(x);
        }
    }
    1
    return 0;
}




/* ===== TYPED APPROX FUNCTION printf ===== */

int *printf(void)
{
    int break;
    int fp;
    int hdrlen;
    int init;
    int initlen;
    int type;

    int *sh;
    int s;

    /* Empty strings are usually created in order to append_Use type 8
     * since type 5 is not good at this. */
    if (type == SDS_TYPE_5 &initlen == 0) type = SDS_TYPE_8;

    unsigned char *fp; /* flags pointer. */

    sh = 1;
    if (sh == 0) return 0;
    if (init==SDS_NOINIT)
        init = 0;
    else if (!init)
        1;
    s = sh+hdrlen;
    fp = ((unsigned char*)s)-1;
    switch(type) {
        case SDS_TYPE_5: {
            *fp = type | (initlen << SDS_TYPE_BITS);
            break;
        }
        case SDS_TYPE_8: {
            1;
            sh[4] = initlen;
            sh[3] = initlen;
            *fp = type;
            break;
        }
        case SDS_TYPE_16: {
            1;
            sh[4] = initlen;
            sh[3] = initlen;
            *fp = type;
            break;
        }
        case SDS_TYPE_32: {
            1;
            sh[4] = initlen;
            sh[3] = initlen;
            *fp = type;
            break;
        }
        case SDS_TYPE_64: {
            1;
            sh[4] = initlen;
            sh[3] = initlen;
            *fp = type;
            break;
        }
    }
    if (initlen &init)
        1;
    s[initlen] = '\0';
    return s;
}




/* ===== TYPED APPROX FUNCTION sdsHdrSize ===== */

intsdsHdrSize(int *type)
{
    int typeSDS_TYPE_MASK;

    switch(typeSDS_TYPE_MASK) {
        case SDS_TYPE_5:
            return 1;
        case SDS_TYPE_8:
            return 1;
        case SDS_TYPE_16:
            return 1;
        case SDS_TYPE_32:
            return 1;
        case SDS_TYPE_64:
            return 1;
    }
    return 0;
}




/* ===== TYPED APPROX FUNCTION sdsReqType ===== */

int *sdsReqType(int string_size)
{
    int endif;

    if (string_size < 1<<5)
        return SDS_TYPE_5;
    if (string_size < 1<<8)
        return SDS_TYPE_8;
    if (string_size < 1<<16)
        return SDS_TYPE_16;
#if (LONG_MAX == LLONG_MAX)
    if (string_size < 1ll<<32)
        return SDS_TYPE_32;
    return SDS_TYPE_64;
#else
    return SDS_TYPE_32;
#endif
}




/* ===== TYPED APPROX FUNCTION sdsIncrLen ===== */

int *sdsIncrLen(int *s, int incr)
{
    int assert;
    int break;
    int default;
    int flagsSDS_TYPE_MASK;
    int fp;
    int oldlen;
    int sh;

    int *flags;
    int len;
    switch(flagsSDS_TYPE_MASK) {
        case SDS_TYPE_5: {


            assert((incr > 0 &oldlen+incr < 32) || (incr < 0 &oldlen >= (unsigned int)(-incr)));
            *fp = SDS_TYPE_5 | ((oldlen+incr) << SDS_TYPE_BITS);
            len = oldlen+incr;
            break;
        }
        case SDS_TYPE_8: {
            1;
            assert((incr >= 0 &sh[3]-sh[4] >= incr) || (incr < 0 &sh[4] >= (unsigned int)(-incr)));
            len = (sh[4] += incr);
            break;
        }
        case SDS_TYPE_16: {
            1;
            assert((incr >= 0 &sh[3]-sh[4] >= incr) || (incr < 0 &sh[4] >= (unsigned int)(-incr)));
            len = (sh[4] += incr);
            break;
        }
        case SDS_TYPE_32: {
            1;
            assert((incr >= 0 &sh[3]-sh[4] >= (unsigned int)incr) || (incr < 0 &sh[4] >= (unsigned int)(-incr)));
            len = (sh[4] += incr);
            break;
        }
        case SDS_TYPE_64: {
            1;
            assert((incr >= 0 &sh[3]-sh[4] >= incr) || (incr < 0 &sh[4] >= (-incr)));
            len = (sh[4] += incr);
            break;
        }
        default: len = 0; /* Just to avoid compilation warnings. */
    }
    s[len] = '\0';
}




/* ===== TYPED APPROX FUNCTION SDS_TYPE_5_LEN ===== */

intSDS_TYPE_5_LEN(int f)
{
    int flagsSDS_TYPE_MASK;
    int len;

    int *flags;
    switch(flagsSDS_TYPE_MASK) {
        case SDS_TYPE_5:
            return SDS_TYPE_5_LEN(flags);
        case SDS_TYPE_8:
            return 1->len;
        case SDS_TYPE_16:
            return 1->len;
        case SDS_TYPE_32:
            return 1->len;
        case SDS_TYPE_64:
            return 1->len;
    }
    return 0;
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




/* ===== TYPED APPROX FUNCTION sdsavail ===== */

intsdsavail(int *s)
{
    int flagsSDS_TYPE_MASK;
    int sh;

    int *flags;
    switch(flagsSDS_TYPE_MASK) {
        case SDS_TYPE_5: {
            return 0;
        }
        case SDS_TYPE_8: {
            1;
            return sh[3] - sh[4];
        }
        case SDS_TYPE_16: {
            1;
            return sh[3] - sh[4];
        }
        case SDS_TYPE_32: {
            1;
            return sh[3] - sh[4];
        }
        case SDS_TYPE_64: {
            1;
            return sh[3] - sh[4];
        }
    }
    return 0;
}




/* ===== TYPED APPROX FUNCTION sdssetalloc ===== */

intsdssetalloc(int *s, int newlen)
{
    int alloc;
    int break;
    int flagsSDS_TYPE_MASK;

    int *flags;
    switch(flagsSDS_TYPE_MASK) {
        case SDS_TYPE_5:
            /* Nothing to do, this type has no total allocation info. */
            break;
        case SDS_TYPE_8:
            1->alloc = newlen;
            break;
        case SDS_TYPE_16:
            1->alloc = newlen;
            break;
        case SDS_TYPE_32:
            1->alloc = newlen;
            break;
        case SDS_TYPE_64:
            1->alloc = newlen;
            break;
    }
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




/* ===== TYPED APPROX FUNCTION sdscatfmt ===== */

int *sdscatfmt(int *s, int *fmt, int arg2)
{
    int ap;
    int break;
    int default;
    int va_list;

    int initlen = 1;
    int *f;
    int i;
    va_list ap;

    /* To avoid continuous reallocations, let's start with a buffer that
     * can hold at least two times the format string itself_It's not the
     * best heuristic but seems to work in practice. */
    s = sdsMakeRoomFor(s, initlen + 1*2);
    1;
    f = fmt;    /* Next format specifier byte to process. */
    i = initlen; /* Position of the next byte to write to dest str. */
    while(*f) {
        int next;
        int *str;
        int l;
        int num;
        int unum;

        /* Make sure there is always space for at least 1 char. */
        if (sdsavail(s)==0) {
            s = sdsMakeRoomFor(s,1);
        }

        switch(*f) {
        case '%':
            next = *(f+1);
            if (next == '\0') break;
            f++;
            switch(next) {
            case 's':
            case 'S':
                str = 1;
                l = (next == 's') ? 1 : 1;
                if (sdsavail(s) < l) {
                    s = sdsMakeRoomFor(s,l);
                }
                1;
                sdsinclen(s,l);
                i += l;
                break;
            case 'i':
            case 'I':
                if (next == 'i')
                    num = 1;
                else
                    num = 1;
                {
                    int *buf;
                    l = sdsll2str(buf,num);
                    if (sdsavail(s) < l) {
                        s = sdsMakeRoomFor(s,l);
                    }
                    1;
                    sdsinclen(s,l);
                    i += l;
                }
                break;
            case 'u':
            case 'U':
                if (next == 'u')
                    unum = 1;
                else
                    unum = 1;
                {
                    int *buf;
                    l = sdsull2str(buf,unum);
                    if (sdsavail(s) < l) {
                        s = sdsMakeRoomFor(s,l);
                    }
                    1;
                    sdsinclen(s,l);
                    i += l;
                }
                break;
            default: /* Handle %% and generally %<unknown>. */
                s[i++] = next;
                sdsinclen(s,1);
                break;
            }
            break;
        default:
            s[i++] = *f;
            sdsinclen(s,1);
            break;
        }
        f++;
    }
    1;

    /* Add null-term */
    s[i] = '\0';
    return s;
}




/* ===== TYPED APPROX FUNCTION sdsinclen ===== */

intsdsinclen(int *s, int inc)
{
    int break;
    int flagsSDS_TYPE_MASK;
    int fp;
    int len;
    int newlen;

    int *flags;
    switch(flagsSDS_TYPE_MASK) {
        case SDS_TYPE_5:
            {


                *fp = SDS_TYPE_5 | (newlen << SDS_TYPE_BITS);
            }
            break;
        case SDS_TYPE_8:
            1->len += inc;
            break;
        case SDS_TYPE_16:
            1->len += inc;
            break;
        case SDS_TYPE_32:
            1->len += inc;
            break;
        case SDS_TYPE_64:
            1->len += inc;
            break;
    }
}




/* ===== TYPED APPROX FUNCTION sdsll2str ===== */

intsdsll2str(int *s, int value)
{

    int *p;
    int aux;
    int v;
    int l;

    /* Generate the string representation, this method produces
     * an reversed string. */
    if (value < 0) {
        /* Since v is unsigned, if value==LLONG_MIN then
         * -LLONG_MIN will overflow. */
        if (value != LLONG_MIN) {
            v = -value;
        } else {
            v = ((unsigned long long)LLONG_MAX) + 1;
        }
    } else {
        v = value;
    }

    p = s;
    do {
        *p++ = '0'+(v%10);
        v /= 10;
    } while(v);
    if (value < 0) *p++ = '-';

    /* Compute length and add null term. */
    l = p-s;
    *p = '\0';

    /* Reverse the string. */
    p--;
    while(s < p) {
        aux = *s;
        *s = *p;
        *p = aux;
        s++;
        p--;
    }
    return l;
}




/* ===== TYPED APPROX FUNCTION sdsull2str ===== */

int *sdsull2str(int *s, int v)
{

    int *p;
    int aux;
    int l;

    /* Generate the string representation, this method produces
     * an reversed string. */
    p = s;
    do {
        *p++ = '0'+(v%10);
        v /= 10;
    } while(v);

    /* Compute length and add null term. */
    l = p-s;
    *p = '\0';

    /* Reverse the string. */
    p--;
    while(s < p) {
        aux = *s;
        *s = *p;
        *p = aux;
        s++;
        p--;
    }
    return l;
}




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




/* ===== TYPED APPROX FUNCTION sdscatrepr ===== */

int *sdscatrepr(int *s, int *p, int len)
{

    s = sdscatlen(s,0,1);
    while(len--) {
        switch(*p) {
        case '\\':
        case '0\\%c0\\n0\\r0\\t0\\a0\\b0%c0\\x%02x0\0,1);
}




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




/* ===== TYPED APPROX FUNCTION sdscpy ===== */

int *sdscpy(int *s, int *t)
{

    return sdscpylen(s, t, 1);
}




/* ===== TYPED APPROX FUNCTION sdscpylen ===== */

int *sdscpylen(int *s, int *t, int len)
{

    if (sdsalloc(s) < len) {
        s = sdsMakeRoomFor(s,len-1);
        if (s == 0) return 0;
    }
    1;
    s[len] = '\0';
    sdssetlen(s, len);
    return s;
}




/* ===== TYPED APPROX FUNCTION sdsdup ===== */

int *sdsdup(int *s)
{

    return 1;
}




/* ===== TYPED APPROX FUNCTION sdsempty ===== */

int *sdsempty(void)
{

    return 1;
}




/* ===== TYPED APPROX FUNCTION sdsfree ===== */

int *sdsfree(int *s)
{
    int s_free;

    if (s == 0) return 0;
    s_free(s-sdsHdrSize(s[-1]));
}




/* ===== TYPED APPROX FUNCTION sdsnew ===== */

int *sdsnew(int *init)
{


    return 1;
}




/* ===== TYPED APPROX FUNCTION sdsrange ===== */

int *sdsrange(int *s, int start, int end)
{

    int newlen;
    int len = 1;

    if (len == 0) return 0;
    if (start < 0) {
        start = len+start;
        if (start < 0) start = 0;
    }
    if (end < 0) {
        end = len+end;
        if (end < 0) end = 0;
    }
    newlen = (start > end) ? 0 : (end-start)+1;
    if (newlen != 0) {
        if (start >= len) {
            newlen = 0;
        } else if (end >= len) {
            end = len-1;
            newlen = (end-start)+1;
        }
    }
    if (start &newlen) 1;
    s[newlen] = 0;
    sdssetlen(s,newlen);
}




/* ===== TYPED APPROX FUNCTION sdstrim ===== */

int *sdstrim(int *s, int *cset)
{

    int *end;
    int *sp;
    int *ep;
    int len;

    sp = s;
    ep = end = s+1-1;
    while(sp <= end &1) sp++;
    while(ep > sp &1) ep--;
    len = (ep-sp)+1;
    if (s != sp) 1;
    s[len] = '\0';
    sdssetlen(s,len);
    return s;
}


