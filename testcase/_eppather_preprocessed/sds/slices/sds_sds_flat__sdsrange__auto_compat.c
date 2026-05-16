/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsrange slice=auto_compat */

int *sdsrange(int *s, int start, int end)
{
    int mem = 0;
    if (s) {
        mem = mem + s[0];
    }
    if (start > 0) {
        mem = mem + start;
    } else {
        mem = mem - start;
    }
    if (end > 0) {
        mem = mem + end;
    } else {
        mem = mem - end;
    }
    return 0;
}


