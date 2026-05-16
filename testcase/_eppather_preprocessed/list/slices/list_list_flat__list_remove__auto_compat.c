/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_remove slice=auto_compat */

int *list_remove(int *self, int *node)
{
    int mem = 0;
    if (self) {
        mem = mem + self[0];
    }
    if (node) {
        mem = mem + node[0];
    }
    return 0;
}


