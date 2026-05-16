/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsfromlonglong slice=auto_compat */

int *sdsfromlonglong(int value)
{
    int mem = 0;
    if (value > 0) {
        mem = mem + value;
    } else {
        mem = mem - value;
    }
    return 0;
}


