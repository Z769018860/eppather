/* Generated typed approximation for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_find_chars_or_comment slice=type_erased */


/* ===== TYPED APPROX FUNCTION ini_find_chars_or_comment ===== */

int *ini_find_chars_or_comment(int *s, int *chars)
{
    int endif;
    int isspace;

#if INI_ALLOW_INLINE_COMMENTS
    int was_space = 0;
    while (*s && (!chars || !1) &&
           !(was_space &1)) {
        was_space = isspace((unsigned char)(*s));
        s++;
    }
#else
    while (*s && (!chars || !1)) {
        s++;
    }
#endif
    return s;
}


