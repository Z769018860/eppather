/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsull2str slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION sdsull2str ===== */

int *sdsull2str(int *s, int v)
{

    int *p;
    int aux;
    int l;

    /* Generate the string representation, this method produces
     * an reversed string. */
    p = s;
    do {
        *p++ = '0'+(v%10);
        v /= 10;
    } while(v);

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


