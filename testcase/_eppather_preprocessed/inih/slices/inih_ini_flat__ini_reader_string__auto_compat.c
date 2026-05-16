/* Generated auto-compatibility summary model for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_reader_string slice=auto_compat */

int *ini_reader_string(int *str, int num, int *stream)
{
    int mem = 0;
    if (str) {
        mem = mem + str[0];
    }
    if (num > 0) {
        mem = mem + num;
    } else {
        mem = mem - num;
    }
    if (stream) {
        mem = mem + stream[0];
    }
    return 0;
}


