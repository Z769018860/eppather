/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sds_realloc slice=auto_compat */

int *sds_realloc(int *ptr, int size)
{
    int mem = 0;
    if (ptr) {
        mem = mem + ptr[0];
    }
    if (size > 0) {
        mem = mem + size;
    } else {
        mem = mem - size;
    }
    return 0;
}


