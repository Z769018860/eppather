/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsrange slice=type_erased */


/* ===== TYPED APPROX FUNCTION sdsrange ===== */

int *sdsrange(int *s, int start, int end)
{

    int newlen;
    int len = 1;

    if (len == 0) return 0;
    if (start < 0) {
        start = len+start;
        if (start < 0) start = 0;
    }
    if (end < 0) {
        end = len+end;
        if (end < 0) end = 0;
    }
    newlen = (start > end) ? 0 : (end-start)+1;
    if (newlen != 0) {
        if (start >= len) {
            newlen = 0;
        } else if (end >= len) {
            end = len-1;
            newlen = (end-start)+1;
        }
    }
    if (start &newlen) 1;
    s[newlen] = 0;
    sdssetlen(s,newlen);
}




/* ===== TYPED APPROX FUNCTION sdssetlen ===== */

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


