/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsfreesplitres slice=auto_compat */

int *sdsfreesplitres(int *tokens, int count)
{
    int mem = 0;
    if (tokens) {
        mem = mem + tokens[0];
    }
    if (count > 0) {
        mem = mem + count;
    } else {
        mem = mem - count;
    }
    return 0;
}


