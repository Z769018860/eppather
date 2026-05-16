/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_strncpy0 slice=auto_compat */

int *ini_strncpy0(int *dest, int *src, int size)
{
    int mem = 0;
    if (dest) {
        mem = mem + dest[0];
    }
    if (src) {
        mem = mem + src[0];
    }
    if (size > 0) {
        mem = mem + size;
    } else {
        mem = mem - size;
    }
    return 0;
}


