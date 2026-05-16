/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsIncrLen slice=auto_compat */

int *sdsIncrLen(int *s, int incr)
{
    int mem = 0;
    if (s) {
        mem = mem + s[0];
    }
    if (incr > 0) {
        mem = mem + incr;
    } else {
        mem = mem - incr;
    }
    return 0;
}


