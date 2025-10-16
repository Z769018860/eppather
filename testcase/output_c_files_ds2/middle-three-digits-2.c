void midThree(char arg[50], int arg_len)
{
    char output[4];
    int midPoint;
    int is_negative;
    int arg_length;
    int i;
    
    is_negative = 0;
    if (arg[0] == '-') {
        is_negative = 1;
    }
    
    arg_length = 0;
    for (i = 0; i < 50; i = i + 1) {
        if (arg[i] == '\0') {
            break;
        }
        arg_length = arg_length + 1;
    }
    
    if (is_negative == 1) {
        midPoint = (arg_length + 1) / 2;
    } else {
        midPoint = (arg_length + 1) / 2 - 1;
    }
    
    if (arg_length < 3) {
        return;
    } else if (arg_length == 3 || arg_length == 4) {
        return;
    } else {
        for (i = 0; i < 3; i = i + 1) {
            output[i] = arg[(midPoint - 1) + i];
        }
        output[3] = '\0';
    }
    return;
}
