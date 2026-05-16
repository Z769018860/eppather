/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsmapchars slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION sdsmapchars ===== */

int *sdsmapchars(int mystring, int ho, int arg2, int arg3)
{
    int break;
    int from;
    int i;
    int j;
    int l;
    int s;
    int setlen;
    int to;



    for (j = 0; j < l; j++) {
        for (i = 0; i < setlen; i++) {
            if (s[j] == from[i]) {
                s[j] = to[i];
                break;
            }
        }
    }
    return s;
}


