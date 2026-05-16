/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdscatrepr slice=auto_compat */

int *sdscatrepr(int *s, int *p, int len)
{
    int mem = 0;
    if (s) {
        mem = mem + s[0];
    }
    if (p) {
        mem = mem + p[0];
    }
    if (len > 0) {
        mem = mem + len;
    } else {
        mem = mem - len;
    }
    return 0;
}


