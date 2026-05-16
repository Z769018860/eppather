/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdscatfmt slice=type_erased */


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




/* ===== TYPED APPROX FUNCTION sdsHdrSize ===== */

int sdsHdrSize(int *type)
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




/* ===== TYPED APPROX FUNCTION sdsavail ===== */

int sdsavail(int *s)
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

int sdssetalloc(int *s, int newlen)
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




/* ===== TYPED APPROX FUNCTION sdsinclen ===== */

int sdsinclen(int *s, int inc)
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




/* ===== TYPED APPROX FUNCTION SDS_TYPE_5_LEN ===== */

int SDS_TYPE_5_LEN(int f)
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




/* ===== TYPED APPROX FUNCTION sdsll2str ===== */

int sdsll2str(int *s, int value)
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


