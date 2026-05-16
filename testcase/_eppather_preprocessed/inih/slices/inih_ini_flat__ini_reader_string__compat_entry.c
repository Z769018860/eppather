/* Generated compatibility slice for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_reader_string slice=compat_entry */


int ini_reader_string(int num_left, int num)
{
    if (num_left == 0 || num < 2) return 0;
    num_left = num_left - 1;
    return num_left + 1;
}


