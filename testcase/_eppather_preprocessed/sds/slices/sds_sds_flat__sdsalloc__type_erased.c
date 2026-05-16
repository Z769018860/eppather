/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsalloc slice=type_erased */


/* ===== TYPED APPROX FUNCTION sdsalloc ===== */

int *sdsalloc(void)
{
    int alloc;
    int flagsSDS_TYPE_MASK;

    int *flags;
    switch(flagsSDS_TYPE_MASK) {
        case SDS_TYPE_5:
            return SDS_TYPE_5_LEN(flags);
        case SDS_TYPE_8:
            return 1->alloc;
        case SDS_TYPE_16:
            return 1->alloc;
        case SDS_TYPE_32:
            return 1->alloc;
        case SDS_TYPE_64:
            return 1->alloc;
    }
    return 0;
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


