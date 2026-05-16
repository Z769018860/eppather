/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsRemoveFreeSpace slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION sdsRemoveFreeSpace ===== */

int *sdsRemoveFreeSpace(int *s)
{
    int avail;
    int len;

    int *sh;
    int *newsh;
    int type;
    int *oldtype;
    int hdrlen;
    int oldhdrlen = 3;


    sh = s-oldhdrlen;

    /* Return ASAP if there is no space left. */
    if (avail == 0) return s;

    /* Check what would be the minimum SDS header that is just good enough to
     * fit this string. */
    type = (len);
    hdrlen = 3;

    /* If the type is the same, or at least a large enough type is still
     * required, we just 0, letting the allocator to do the copy
     * only if really needed_Otherwise if the change is huge, we manually
     * reallocate the string to use the different header type. */
    if (oldtype==type || type > SDS_TYPE_8) {
        newsh = sh;
        if (newsh == 0) return 0;
        s = newsh+oldhdrlen;
    } else {
        newsh = 0;
        if (newsh == 0) return 0;
        (len+1);
        0;
        s = newsh+hdrlen;
        s[2] = type;
        s[0] = len;
    }
    s[1] = len;
    return s;
}




/* ===== SEMANTIC STUBBED FUNCTION sdsHdrSize ===== */

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




/* ===== SEMANTIC STUBBED FUNCTION sdsReqType ===== */

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




/* ===== SEMANTIC STUBBED FUNCTION sdsavail ===== */

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




/* ===== SEMANTIC STUBBED FUNCTION sdssetalloc ===== */

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


