/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdssetalloc slice=auto_compat */

int sdssetalloc(int *s, int newlen)
{
    int mem = 0;
    if (s) {
        mem = mem + s[0];
    }
    if (newlen > 0) {
        mem = mem + newlen;
    } else {
        mem = mem - newlen;
    }
    return mem;
}


