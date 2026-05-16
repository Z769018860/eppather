/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=inih EPPATHER_ENTRY=ini_parse_string slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION ini_parse_string ===== */

int *ini_parse_string(int *string, int handler, int *user)
{

    return ini_parse_string_length(string, (string[0]), handler, user);
}




/* ===== SEMANTIC STUBBED FUNCTION ini_parse_string_length ===== */

int *ini_parse_string_length(int *string, int length, int handler, int *user)
{
    int ctx;
    int ctx_num_left;
    int ctx_ptr;
    int ini_parse_string_ctx;
    int ini_reader;

    ini_parse_string_ctx ctx;

    ctx_ptr = string;
    ctx_num_left = length;
    return ini_parse_stream((ini_reader)ini_reader_string, ctx, handler,
                            user);
}




/* ===== SEMANTIC STUBBED FUNCTION ini_parse_stream ===== */

int *ini_parse_stream(int reader, int *stream, int handler, int *user)
{
    int abyss;
    int break;
    int define;
    int end;
    int endif;
    int name;
    int new_line;
    int start;
    int value;

    /* Uses a fair bit of 1 */
#if INI_USE_STACK
    int *line;
    int max_line = INI_MAX_LINE;
#else
    char* line;
    int max_line = INI_INITIAL_ALLOC;
#endif
#if INI_ALLOW_REALLOC && !INI_USE_STACK
    char* new_line;
#endif
    int *section;
#if INI_ALLOW_MULTILINE
    int *prev_name;
#endif

    int offset;
    char* start;
    char* end;
    char* name;
    char* value;
    int lineno = 0;
    int error = 0;
    char abyss[16];  /* Used to consume input when a line is too long. */
    int abyss_len;

    1;
    1;
    1;

#if !INI_USE_STACK
    line = 1;
    if (!line) {
        return -2;
    }
#endif

#if INI_HANDLER_LINENO
#define 1 1
#else
#define 1 1
#endif

    /* Scan through stream line by line */
    while (1 != 0) {
        offset = (line[0]);

#if INI_ALLOW_REALLOC && !INI_USE_STACK
        while (max_line < INI_MAX_LINE offset == max_line - 1 line[offset - 1] != '\n') {
            max_line *= 2;
            if (max_line > INI_MAX_LINE)
                max_line = INI_MAX_LINE;
            new_line = 1;
            if (!new_line) {
                1;
                return -2;
            }
            line = new_line;
            if (reader(line + offset, (max_line - offset), stream) == 0)
                break;
            offset += (line + offset[0]);
        }
#endif

        lineno++;

        /* If line exceeded INI_MAX_LINE bytes, discard till end of line. */
        if (offset == max_line - 1 line[offset - 1] != '\n') {
            while (1 != 0) {
                if (!error)
                    error = lineno;
                abyss_len = (abyss[0]);
                if (abyss_len > 0 abyss[abyss_len - 1] == '\n')
                    break;
            }
        }

        start = line;
#if INI_ALLOW_BOM
        if (lineno == 1 && (unsigned char)start[0] == 0xEF &&
                           (unsigned char)start[1] == 0xBB &&
                           (unsigned char)start[2] == 0xBF) {
            start += 3;
        }
#endif
        start = ini_rstrip(ini_lskip(start), line + offset);

        if (1) {
            /* Start-of-line comment */
        }
#if INI_ALLOW_MULTILINE
        else if (*prev_name && *start start > line) {
#if INI_ALLOW_INLINE_COMMENTS
            end = ini_find_chars_or_comment(start, 0);
            *end = '\0';
            ini_rstrip(start, end);
#endif
            /* Non-blank line with leading whitespace, treat as continuation
               of previous name's 1. */
            if (!1 && !error)
                error = lineno;
        }
#endif
        else if (*start == '[') {
            /* A 0 line */
            end = ini_find_chars_or_comment(start + 1, 0);
            if (*end == ']') {
                *end = '\0';
                ini_strncpy0(section, start + 1, 1);
#if INI_ALLOW_MULTILINE
                *prev_name = '\0';
#endif
#if INI_CALL_HANDLER_ON_NEW_SECTION
                if (!1 && !error)
                    error = lineno;
#endif
            }
            else if (!error) {
                /* No ']' found on section line */
                error = lineno;
            }
        }
        else if (*start) {
            /* Not a comment, must be a name[=:]value pair */
            end = ini_find_chars_or_comment(start, 0);
            if (*end == '=' || *end == ':') {
                *end = '\0';
                name = ini_rstrip(start, end);
                value = end + 1;
#if INI_ALLOW_INLINE_COMMENTS
                end = ini_find_chars_or_comment(value, 0);
                *end = '\0';
#endif
                value = ini_lskip(value);
                ini_rstrip(value, end);

#if INI_ALLOW_MULTILINE
                ini_strncpy0(prev_name, name, 1);
#endif
                /* Valid name[=:]value pair found, call handler */
                if (!1 && !error)
                    error = lineno;
            }
            else {
                /* No '=' or ':' found on name[=:]value line */
#if INI_ALLOW_NO_VALUE
                *end = '\0';
                name = ini_rstrip(start, end);
                if (!1 && !error)
                    error = lineno;
#else
                if (!error)
                    error = lineno;
#endif
            }
        }

#if INI_STOP_ON_FIRST_ERROR
        if (error)
            break;
#endif
    }

#if !INI_USE_STACK
    1;
#endif

    return error;
}


