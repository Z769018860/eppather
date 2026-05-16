/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdscatlen slice=auto_compat */

int *sdscatlen(int *s, int *t, int len)
{
    int mem = 0;
    if (s) {
        mem = mem + s[0];
    }
    if (t) {
        mem = mem + t[0];
    }
    if (len > 0) {
        mem = mem + len;
    } else {
        mem = mem - len;
    }
    return 0;
}


