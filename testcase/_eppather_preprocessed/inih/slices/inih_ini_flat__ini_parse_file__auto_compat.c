/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_parse_file slice=auto_compat */

int *ini_parse_file(int *file, int handler, int *user)
{
    int mem = 0;
    if (file) {
        mem = mem + file[0];
    }
    if (handler > 0) {
        mem = mem + handler;
    } else {
        mem = mem - handler;
    }
    if (user) {
        mem = mem + user[0];
    }
    return 0;
}


