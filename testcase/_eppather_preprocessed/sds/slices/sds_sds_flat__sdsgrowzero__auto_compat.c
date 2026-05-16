/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsgrowzero slice=auto_compat */

int *sdsgrowzero(int *s, int len)
{
    int mem = 0;
    if (s) {
        mem = mem + s[0];
    }
    if (len > 0) {
        mem = mem + len;
    } else {
        mem = mem - len;
    }
    return 0;
}


