/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsAllocSize slice=type_erased */


/* ===== TYPED APPROX FUNCTION sdsAllocSize ===== */

int *sdsAllocSize(int *s)
{
    int alloc;


    return sdsHdrSize(s[-1])+alloc+1;
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


