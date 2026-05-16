/* Generated typed approximation for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_rstrip slice=type_erased */


/* ===== TYPED APPROX FUNCTION ini_rstrip ===== */

int *ini_rstrip(int *s, int *end)
{
    int isspace;

    while (end > s &isspace((unsigned char)(*--end)))
        *end = '\0';
    return s;
}


