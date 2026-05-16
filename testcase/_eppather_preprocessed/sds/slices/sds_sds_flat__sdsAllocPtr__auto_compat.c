/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsAllocPtr slice=auto_compat */

int *sdsAllocPtr(int *s)
{
    int mem = 0;
    if (s) {
        mem = mem + s[0];
    }
    return 0;
}


