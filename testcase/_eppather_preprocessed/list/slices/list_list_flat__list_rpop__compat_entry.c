/* Generated compatibility slice for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_rpop slice=compat_entry */


int list_rpop(int len)
{
    int reads = 1;
    if (!len) return 0;
    len = len - 1;
    if (len) reads = reads + 3;
    else reads = reads + 2;
    return reads + len;
}


