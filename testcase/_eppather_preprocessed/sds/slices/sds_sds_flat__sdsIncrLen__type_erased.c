/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsIncrLen slice=type_erased */


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


