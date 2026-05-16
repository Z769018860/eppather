/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsinclen slice=auto_compat */

int sdsinclen(int *s, int inc)
{
    int mem = 0;
    if (s) {
        mem = mem + s[0];
    }
    if (inc > 0) {
        mem = mem + inc;
    } else {
        mem = mem - inc;
    }
    return mem;
}


