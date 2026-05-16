/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdstrim slice=auto_compat */

int *sdstrim(int *s, int *cset)
{
    int mem = 0;
    if (s) {
        mem = mem + s[0];
    }
    if (cset) {
        mem = mem + cset[0];
    }
    return 0;
}


