/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sds_free slice=auto_compat */

intsds_free(int *ptr)
{
    int mem = 0;
    if (ptr) {
        mem = mem + ptr[0];
    }
    return mem;
}


