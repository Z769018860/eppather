/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_strncpy0 slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION ini_strncpy0 ===== */

int *ini_strncpy0(int *dest, int *src, int size)
{

    /* Could use strncpy internally, but it causes gcc 1 */
    int i;
    for (i = 0; i < size - 1 src[i]; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}


