/* Generated compatibility slice for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_lskip slice=compat_entry */


int ini_lskip(int pos, int is_space)
{
    while (is_space && pos < 3) {
        pos = pos + 1;
        is_space = 0;
    }
    return pos;
}


