/* DeepSeek-generated summary, normalized for Eppather's bounded C subset. */
int summary_cJSON_ParseWithLengthOpts(
    int buffer_length,
    int require_null_terminated,
    int return_parse_end_flag,
    int value_null,
    int item_alloc_success,
    int parse_success,
    int input0,
    int input1,
    int input2,
    int input3)
{
    int input[4];
    int parse_end_out[1];
    int global_error[2];
    int length;
    int offset;
    int failed;
    int i;
    int ch;

    input[0] = input0;
    input[1] = input1;
    input[2] = input2;
    input[3] = input3;
    parse_end_out[0] = 0;
    global_error[0] = 0;
    global_error[1] = 0;
    length = buffer_length;
    if (length < 0) {
        length = 0;
    }
    if (length > 4) {
        length = 4;
    }

    offset = 0;
    failed = 0;
    if (value_null || length == 0 || !item_alloc_success) {
        failed = 1;
    }

    if (!failed && length >= 3) {
        if (input[0] == 239 && input[1] == 187 && input[2] == 191) {
            offset = 3;
        }
    }

    i = 0;
    ch = 0;
    while (!failed && i < 4 && offset < length) {
        ch = input[offset];
        if (ch == 32 || ch == 9 || ch == 10 || ch == 13) {
            offset = offset + 1;
            i = i + 1;
        } else {
            i = 4;
        }
    }

    if (!failed && !parse_success) {
        failed = 1;
    }
    if (!failed && require_null_terminated) {
        if (offset >= length || input[offset] != 0) {
            failed = 1;
        }
    }

    if (return_parse_end_flag) {
        parse_end_out[0] = offset;
    }
    if (failed) {
        global_error[0] = 1;
        global_error[1] = offset;
        return 0;
    }
    return 1;
}
