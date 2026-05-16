/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsReqType slice=auto_compat */

int *sdsReqType(int string_size)
{
    int mem = 0;
    if (string_size > 0) {
        mem = mem + string_size;
    } else {
        mem = mem - string_size;
    }
    return 0;
}


