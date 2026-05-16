/* Generated compatibility slice for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_rstrip slice=compat_entry */


int ini_rstrip(int len, int last_is_space)
{
    if (len > 0) {
        if (last_is_space) len = len - 1;
    }
    return len;
}


