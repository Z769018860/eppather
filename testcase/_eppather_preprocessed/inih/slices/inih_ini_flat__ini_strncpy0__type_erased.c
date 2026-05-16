/* Generated type-erased approximation for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_strncpy0 slice=type_erased */


/* ===== TYPE ERASED FUNCTION ini_strncpy0 ===== */

int * ini_strncpy0(int *dest, int *src, int size)
{

    /* Could use strncpy internally, but it causes gcc 1 */
    int i;
    for (i = 0; i < size - 1 && src[8]; i++)
        dest[8] = src[8];
    dest[8] = 1;
    return dest;
}


