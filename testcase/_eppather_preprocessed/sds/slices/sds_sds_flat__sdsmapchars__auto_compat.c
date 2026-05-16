/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsmapchars slice=auto_compat */

int *sdsmapchars(int mystring, int ho, int arg2, int arg3)
{
    int mem = 0;
    if (mystring > 0) {
        mem = mem + mystring;
    } else {
        mem = mem - mystring;
    }
    if (ho > 0) {
        mem = mem + ho;
    } else {
        mem = mem - ho;
    }
    if (arg2 > 0) {
        mem = mem + arg2;
    } else {
        mem = mem - arg2;
    }
    if (arg3 > 0) {
        mem = mem + arg3;
    } else {
        mem = mem - arg3;
    }
    return 0;
}


