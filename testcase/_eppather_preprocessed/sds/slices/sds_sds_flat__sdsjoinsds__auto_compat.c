/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=sds EPPATHER_ENTRY=sdsjoinsds slice=auto_compat */

int *sdsjoinsds(int *argv, int argc, int *sep, int seplen)
{
    int mem = 0;
    if (argv) {
        mem = mem + argv[0];
    }
    if (argc > 0) {
        mem = mem + argc;
    } else {
        mem = mem - argc;
    }
    if (sep) {
        mem = mem + sep[0];
    }
    if (seplen > 0) {
        mem = mem + seplen;
    } else {
        mem = mem - seplen;
    }
    return 0;
}


