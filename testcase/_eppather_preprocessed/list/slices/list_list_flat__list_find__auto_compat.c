/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_find slice=auto_compat */

int *list_find(int *self, int *val)
{
    int mem = 0;
    if (self) {
        mem = mem + self[0];
    }
    if (val) {
        mem = mem + val[0];
    }
    return 0;
}


