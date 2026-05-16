/* Generated type-erased approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsReqType slice=type_erased */


/* ===== TYPE ERASED FUNCTION sdsReqType ===== */

int sdsReqType(int string_size)
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


