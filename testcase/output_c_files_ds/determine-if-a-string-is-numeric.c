int isNumeric(const char *s) {
    int result;
    int i;
    int has_digit;
    int has_dot;
    int has_sign;
    if (s == 0 || *s == 0) {
        result = 0;
        return result;
    }
    i = 0;
    has_digit = 0;
    has_dot = 0;
    has_sign = 0;
    if (s[i] == '+' || s[i] == '-') {
        has_sign = 1;
        i = i + 1;
    }
    for (; s[i] != 0; i = i + 1) {
        if (s[i] >= '0' && s[i] <= '9') {
            has_digit = 1;
        } else if (s[i] == '.') {
            if (has_dot == 1) {
                result = 0;
                return result;
            }
            has_dot = 1;
        } else {
            result = 0;
            return result;
        }
    }
    if (has_digit == 0) {
        result = 0;
        return result;
    }
    result = 1;
    return result;
}
