/* Generated compatibility slice for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsReqType slice=compat_entry */


int sdsReqType(unsigned long string_size)
{
    if (string_size < 32) {
        return 0;
    }
    if (string_size < 256) {
        return 1;
    }
    if (string_size < 65536) {
        return 2;
    }
    return 3;
}


