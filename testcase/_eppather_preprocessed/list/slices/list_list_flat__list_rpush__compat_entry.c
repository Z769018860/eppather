/* Generated compatibility slice for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_rpush slice=compat_entry */


int list_rpush(int len, int node_ok)
{
    int writes = 0;
    if (!node_ok) return 0;
    if (len) writes = writes + 4;
    else writes = writes + 4;
    len = len + 1;
    return writes + len;
}


