/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsfree slice=type_erased */


/* ===== TYPED APPROX FUNCTION sdsfree ===== */

int *sdsfree(int *s)
{
    int s_free;

    if (s == 0) return 0;
    s_free(s-sdsHdrSize(s[-1]));
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


