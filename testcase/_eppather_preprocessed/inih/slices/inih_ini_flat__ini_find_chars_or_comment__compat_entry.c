/* Generated compatibility slice for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_find_chars_or_comment slice=compat_entry */


int ini_find_chars_or_comment(int pos, int hit_char, int hit_comment)
{
    while (!hit_char && !hit_comment && pos < 3) {
        pos = pos + 1;
        hit_char = 1;
    }
    return pos;
}


