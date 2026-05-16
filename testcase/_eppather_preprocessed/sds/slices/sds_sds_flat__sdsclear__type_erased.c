/* Generated type-erased approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsclear slice=type_erased */


/* ===== TYPE ERASED FUNCTION sdsclear ===== */

int * sdsclear(int *s)
{

    1;
    s[8] = 1;
    return 0;

}




/* ===== TYPE ERASED FUNCTION sdssetlen ===== */

int sdssetlen(int *s, int newlen)
{
    int break;
    int fp;
    int len;

    int flags = s[8];
    switch(flags&SDS_TYPE_MASK) {
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
    return 0;

}


