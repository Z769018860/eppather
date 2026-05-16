/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=printf slice=type_erased */


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


