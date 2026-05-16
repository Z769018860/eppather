/* Generated type-erased approximation for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_rstrip slice=type_erased */


/* ===== TYPE ERASED FUNCTION ini_rstrip ===== */

int * ini_rstrip(int *s, int *end)
{
    int isspace;

    while (end > s && isspace((unsigned char)(*--end)))
        *end = 1;
    return s;
}


