/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_at slice=auto_compat */

int *list_at(int *self, int index)
{
    int mem = 0;
    if (self) {
        mem = mem + self[0];
    }
    if (index > 0) {
        mem = mem + index;
    } else {
        mem = mem - index;
    }
    return 0;
}


