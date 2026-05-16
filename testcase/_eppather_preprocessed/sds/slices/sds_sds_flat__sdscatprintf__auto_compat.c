/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdscatprintf slice=auto_compat */

int *sdscatprintf(int *s, int *fmt, int arg2)
{
    int mem = 0;
    if (s) {
        mem = mem + s[0];
    }
    if (fmt) {
        mem = mem + fmt[0];
    }
    if (arg2 > 0) {
        mem = mem + arg2;
    } else {
        mem = mem - arg2;
    }
    return 0;
}


