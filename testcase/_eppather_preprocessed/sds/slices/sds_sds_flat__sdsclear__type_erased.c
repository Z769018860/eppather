/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsclear slice=type_erased */


/* ===== TYPED APPROX FUNCTION sdsclear ===== */

int *sdsclear(int *s)
{

    sdssetlen(s, 0);
    s[0] = '\0';
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


