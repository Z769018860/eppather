/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsfromlonglong slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION sdsfromlonglong ===== */

int *sdsfromlonglong(int value)
{

    int *buf;


    return 1;
}




/* ===== SEMANTIC STUBBED FUNCTION sdsll2str ===== */

int sdsll2str(int *s, int value)
{

    int *p;
    int aux;
    int v;
    int l;

    /* Generate the string representation, this method produces
     * an reversed string. */
    if (value < 0) {
        /* Since v is unsigned, if value==LLONG_MIN then
         * -LLONG_MIN will overflow. */
        if (value != LLONG_MIN) {
            v = -value;
        } else {
            v = ((unsigned long long)LLONG_MAX) + 1;
        }
    } else {
        v = value;
    }

    p = s;
    do {
        *p++ = '0'+(v%10);
        v /= 10;
    } while(v);
    if (value < 0) *p++ = '-';

    /* Compute length and add null term. */
    l = p-s;
    *p = '\0';

    /* Reverse the string. */
    p--;
    while(s < p) {
        aux = *s;
        *s = *p;
        *p = aux;
        s++;
        p--;
    }
    return l;
}


