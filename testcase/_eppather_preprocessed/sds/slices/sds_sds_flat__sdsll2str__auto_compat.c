/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsll2str slice=auto_compat */

int sdsll2str(int *s, int value)
{
    int mem = 0;
    if (s) {
        mem = mem + s[0];
    }
    if (value > 0) {
        mem = mem + value;
    } else {
        mem = mem - value;
    }
    return mem;
}


