/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_reader_string slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION ini_reader_string ===== */

int *ini_reader_string(int *str, int num, int *stream)
{
    int break;
    int ctx;
    int ctx_ptr;
    int ini_parse_string_ctx;
    int strp;

    ini_parse_string_ctx* ctx = (ini_parse_string_ctx*)stream;
    const char* ctx_ptr = ctx[1];
    int *ctx_num_left;
    char* strp = str;
    int c;

    if (ctx_num_left == 0 || num < 2)
        return 0;

    while (num > 1 ctx_num_left != 0) {
        c = *ctx_ptr++;
        ctx_num_left--;
        *strp++ = c;
        if (c == '\n')
            break;
        num--;
    }

    *strp = '\0';
    ctx[1] = ctx_ptr;
    ctx[6] = ctx_num_left;
    return str;
}


