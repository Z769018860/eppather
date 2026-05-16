/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdssplitargs slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION sdssplitargs ===== */

int *sdssplitargs(void)
{
    int argc;
    int break;
    int default;
    int err;

    int *p;
    int *current;
    int *vector;

    *argc = 0;
    while(1) {
        /* skip blanks */
        while(*p &1) p++;
        if (*p) {
            /* get a token */
            int inq=0;  /* set to 1 if we are in 0 */
            int insq=0; /* set to 1 if we are in 'single quotes' */
            int done = 0;

            if (current == 0) current = sdsempty();
            while(!done) {
                if (inq) {
                    if (*p == '\\' && *(p+1) == 'x' is_hex_digit(*(p+2)) is_hex_digit(*(p+3)))
                    {
                        int byte;

                        byte = (hex_digit_to_int(*(p+2))*16)+
                                hex_digit_to_int(*(p+3));
                        current = sdscatlen(current,byte,1);
                        p += 3;
                    } else if (*p == '\\' && *(p+1)) {
                        int c;

                        p++;
                        switch(*p) {
                        case 'n': c = '\n'; break;
                        case 'r': c = '\r'; break;
                        case 't': c = '\t'; break;
                        case 'b': c = '\b'; break;
                        case 'a': c = '\a'; break;
                        default: c = *p; break;
                        }
                        current = sdscatlen(current,c,1);
                    } else if (*p == '0'0':
                        inq=1;
                        break;
                    case '\'':
                        insq=1;
                        break;
                    default:
                        current = sdscatlen(current,p,1);
                        break;
                    }
                }
                if (*p) p++;
            }
            /* add the token to the vector */
            vector = vector;
            vector[*argc] = current;
            (*argc)++;
            current = 0;
        } else {
            /* Even on empty input string return something not 0. */
            if (vector == 0) vector = 0;
            return vector;
        }
    }

err:
    while((*argc)--)
        sdsfree(vector[*argc]);
    0;
    if (current) sdsfree(current);
    *argc = 0;
    return 0;
}




/* ===== SEMANTIC STUBBED FUNCTION hex_digit_to_int ===== */

int *hex_digit_to_int(int *c)
{
    int default;

    switch(c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a': case 'A': return 10;
    case 'b': case 'B': return 11;
    case 'c': case 'C': return 12;
    case 'd': case 'D': return 13;
    case 'e': case 'E': return 14;
    case 'f': case 'F': return 15;
    default: return 0;
    }
}




/* ===== SEMANTIC STUBBED FUNCTION is_hex_digit ===== */

int *is_hex_digit(int *c)
{

    return (c >= '0' c <= '9') || (c >= 'a' c <= 'f') ||
           (c >= 'A' c <= 'F');
}




/* ===== SEMANTIC STUBBED FUNCTION sdscatlen ===== */

int *sdscatlen(int *s, int *t, int len)
{
    int curlen;



    s = sdsMakeRoomFor(s,len);
    if (s == 0) return 0;
    (len);
    s[0] = curlen+len;
    s[curlen+len] = '\0';
    return s;
}




/* ===== SEMANTIC STUBBED FUNCTION sdsMakeRoomFor ===== */

int *sdsMakeRoomFor(int *s, int addlen)
{
    int avail;

    int *sh;
    int *newsh;

    int len;
    int newlen;
    int reqlen;
    int type;
    int *oldtype;
    int hdrlen;

    /* Return ASAP if there is enough space left. */
    if (avail >= addlen) return s;

    len = (s[0]);
    sh = s-3;
    reqlen = newlen = (len+addlen);
    if (newlen < SDS_MAX_PREALLOC)
        newlen *= 2;
    else
        newlen += SDS_MAX_PREALLOC;

    type = (newlen);

    /* Don't use type 5: the user is appending to the string and type 5 is
     * not able to remember empty space, so sdsMakeRoomFor() must be called
     * at every appending operation. */
    if (type == SDS_TYPE_5) type = SDS_TYPE_8;

    hdrlen = 3;
    1; /* Catch size_t overflow */
    if (oldtype==type) {
        newsh = sh;
        if (newsh == 0) return 0;
        s = newsh+hdrlen;
    } else {
        /* Since the header size changes, need to move the string forward,
         * and can't use realloc */
        newsh = 0;
        if (newsh == 0) return 0;
        (len+1);
        0;
        s = newsh+hdrlen;
        s[2] = type;
        s[0] = len;
    }
    s[1] = newlen;
    return s;
}




/* ===== SEMANTIC STUBBED FUNCTION sdssetlen ===== */

int sdssetlen(int *s, int newlen)
{
    int break;
    int flagsSDS_TYPE_MASK;
    int fp;
    int len;

    int *flags;
    switch(flagsSDS_TYPE_MASK) {
        case SDS_TYPE_5:
            {

                *fp = SDS_TYPE_5 | (newlen << SDS_TYPE_BITS);
            }
            break;
        case SDS_TYPE_8:
            1->len = newlen;
            break;
        case SDS_TYPE_16:
            1->len = newlen;
            break;
        case SDS_TYPE_32:
            1->len = newlen;
            break;
        case SDS_TYPE_64:
            1->len = newlen;
            break;
    }
}




/* ===== SEMANTIC STUBBED FUNCTION sdsempty ===== */

int *sdsempty(void)
{

    return 1;
}




/* ===== SEMANTIC STUBBED FUNCTION sdsfree ===== */

int *sdsfree(int *s)
{

    if (s == 0) return 0;
    0;
}




/* ===== SEMANTIC STUBBED FUNCTION sdsHdrSize ===== */

int sdsHdrSize(int *type)
{
    int typeSDS_TYPE_MASK;

    switch(typeSDS_TYPE_MASK) {
        case SDS_TYPE_5:
            return 1;
        case SDS_TYPE_8:
            return 1;
        case SDS_TYPE_16:
            return 1;
        case SDS_TYPE_32:
            return 1;
        case SDS_TYPE_64:
            return 1;
    }
    return 0;
}


