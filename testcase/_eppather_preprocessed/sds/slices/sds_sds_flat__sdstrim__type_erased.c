/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdstrim slice=type_erased */


/* ===== TYPED APPROX FUNCTION sdstrim ===== */

int *sdstrim(int *s, int *cset)
{

    int *end;
    int *sp;
    int *ep;
    int len;

    sp = s;
    ep = end = s+1-1;
    while(sp <= end &1) sp++;
    while(ep > sp &1) ep--;
    len = (ep-sp)+1;
    if (s != sp) 1;
    s[len] = '\0';
    sdssetlen(s,len);
    return s;
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


