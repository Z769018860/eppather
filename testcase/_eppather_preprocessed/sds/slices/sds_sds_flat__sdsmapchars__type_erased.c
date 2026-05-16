/* Generated typed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsmapchars slice=type_erased */


/* ===== TYPED APPROX FUNCTION sdsmapchars ===== */

int *sdsmapchars(int mystring, int ho, int arg2, int arg3)
{
    int break;
    int from;
    int s;
    int setlen;
    int to;

    int j;
    int i;
    int l = 1;

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


