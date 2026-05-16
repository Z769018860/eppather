/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_parse_stream slice=auto_compat */

int *ini_parse_stream(int reader, int *stream, int handler, int *user)
{
    int mem = 0;
    if (reader > 0) {
        mem = mem + reader;
    } else {
        mem = mem - reader;
    }
    if (stream) {
        mem = mem + stream[0];
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


