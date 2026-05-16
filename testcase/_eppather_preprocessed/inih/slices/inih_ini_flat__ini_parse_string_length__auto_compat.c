/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_parse_string_length slice=auto_compat */

int *ini_parse_string_length(int *string, int length, int handler, int *user)
{
    int mem = 0;
    if (string) {
        mem = mem + string[0];
    }
    if (length > 0) {
        mem = mem + length;
    } else {
        mem = mem - length;
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


