/* Generated compatibility slice for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_remove slice=compat_entry */


int list_remove(int has_prev, int has_next, int len)
{
    int writes = 0;
    if (has_prev) writes = writes + 1;
    else writes = writes + 1;
    if (has_next) writes = writes + 1;
    else writes = writes + 1;
    len = len - 1;
    return writes + len;
}


