/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsHdrSize slice=auto_compat */

int sdsHdrSize(int *type)
{
    int mem = 0;
    if (type) {
        mem = mem + type[0];
    }
    return mem;
}


