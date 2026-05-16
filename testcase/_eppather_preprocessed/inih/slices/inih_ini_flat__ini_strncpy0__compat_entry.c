/* Generated compatibility slice for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_strncpy0 slice=compat_entry */


int ini_strncpy0(int size, int src_nonzero)
{
    int copied = 0;
    if (size > 1) {
        if (src_nonzero) {
            copied = copied + 1;
        }
    }
    return copied;
}


