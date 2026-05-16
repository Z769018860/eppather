/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsfreesplitres slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION sdsfreesplitres ===== */

int *sdsfreesplitres(int *tokens, int count)
{

    if (!tokens) return 0;
    while(count--)
        sdsfree(tokens[count]);
    0;
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


