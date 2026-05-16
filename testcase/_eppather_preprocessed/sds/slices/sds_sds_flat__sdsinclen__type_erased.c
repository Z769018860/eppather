/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsinclen slice=type_erased */


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


