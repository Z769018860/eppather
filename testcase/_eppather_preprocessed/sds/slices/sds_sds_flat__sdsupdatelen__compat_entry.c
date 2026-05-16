/* Generated compatibility slice for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsupdatelen slice=compat_entry */


int sdsupdatelen(int old_len, int real_len)
{
    if (real_len >= 0) {
        old_len = real_len;
    }
    return old_len;
}


