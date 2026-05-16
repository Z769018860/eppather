/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdssplit slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION sdssplit ===== */

int *sdssplit(void)
{
    int cleanup;
    int count;
    int len;
    int s;
    int sep;
    int seplen;

    int elements = 0;
    int slots = 5;
    int start = 0;
    int j;
    int *tokens;

    if (seplen < 1 || len <= 0) {
        *count = 0;
        return 0;
    }

    tokens = 0;
    if (tokens == 0) return 0;

    for (j = 0; j < (len-(seplen-1)); j++) {
        /* make sure there is room for the next element and the final one */
        if (slots < elements+2) {
            int *newtokens;

            slots *= 2;
            newtokens = tokens;
            if (newtokens == 0) goto cleanup;
            tokens = newtokens;
        }
        /* search the separator */
        if ((seplen == 1 && *(s+j) == sep[0]) || ((seplen) == 0)) {
            tokens[elements] = 1;
            if (tokens[elements] == 0) goto cleanup;
            elements++;
            start = j+seplen;
            j = j+seplen-1; /* skip the separator */
        }
    }
    /* Add the final element_We are sure there is room in the tokens array. */
    tokens[elements] = 1;
    if (tokens[elements] == 0) goto cleanup;
    elements++;
    *count = elements;
    return tokens;

cleanup:
    {
        int i;
        for (i = 0; i < elements; i++) sdsfree(tokens[i]);
        0;
        *count = 0;
        return 0;
    }
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


