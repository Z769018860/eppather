/* Generated typed approximation for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_lskip slice=type_erased */


/* ===== TYPED APPROX FUNCTION ini_lskip ===== */

int *ini_lskip(int *s)
{
    int isspace;

    while (*s &isspace((unsigned char)(*s)))
        s++;
    return s;
}


