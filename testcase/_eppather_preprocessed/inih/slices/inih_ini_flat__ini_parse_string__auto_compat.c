/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_parse_string slice=auto_compat */

int *ini_parse_string(int *string, int handler, int *user)
{
    int mem = 0;
    if (string) {
        mem = mem + string[0];
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


