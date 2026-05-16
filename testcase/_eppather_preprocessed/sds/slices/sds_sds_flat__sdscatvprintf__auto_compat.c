/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdscatvprintf slice=auto_compat */

int *sdscatvprintf(int *s, int *fmt, int ap)
{
    int mem = 0;
    if (s) {
        mem = mem + s[0];
    }
    if (fmt) {
        mem = mem + fmt[0];
    }
    if (ap > 0) {
        mem = mem + ap;
    } else {
        mem = mem - ap;
    }
    return 0;
}


