/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsull2str slice=auto_compat */

int *sdsull2str(int *s, int v)
{
    int mem = 0;
    if (s) {
        mem = mem + s[0];
    }
    if (v > 0) {
        mem = mem + v;
    } else {
        mem = mem - v;
    }
    return 0;
}


