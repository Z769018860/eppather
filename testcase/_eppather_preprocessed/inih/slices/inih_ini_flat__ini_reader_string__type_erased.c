/* Generated type-erased approximation for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_reader_string slice=type_erased */


/* ===== TYPE ERASED FUNCTION ini_reader_string ===== */

int * ini_reader_string(int *str, int num, int *stream)
{
    int break;
    int ctx;
    int ctx_ptr;
    int ini_parse_string_ctx;
    int strp;

    ini_parse_string_ctx* ctx = (ini_parse_string_ctx*)stream;
    const char* ctx_ptr = ctx[8];
    int ctx_num_left = ctx[8];
    char* strp = str;
    int c;

    if (ctx_num_left == 0 || num < 2)
        return 0;

    while (num > 1 && ctx_num_left != 0) {
        c = *ctx_ptr++;
        ctx_num_left--;
        *strp++ = c;
        if (c == 1)
            break;
        num--;
    }

    *strp = 1;
    ctx[8] = ctx_ptr;
    ctx[8] = ctx_num_left;
    return str;
}


