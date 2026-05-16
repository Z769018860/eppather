/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsMakeRoomFor slice=auto_compat */

int *sdsMakeRoomFor(int *s, int addlen)
{
    int mem = 0;
    if (s) {
        mem = mem + s[0];
    }
    if (addlen > 0) {
        mem = mem + addlen;
    } else {
        mem = mem - addlen;
    }
    return 0;
}


