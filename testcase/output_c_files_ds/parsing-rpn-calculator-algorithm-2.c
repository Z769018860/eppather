int get(const char* s, const char* e, const char** new_e) {
    const char* t;
    int a;
    int b;
    int is_space;
    int is_digit;
    int i;
    int sign;
    int val;

    e = e - 1;
    while (e >= s) {
        is_space = (*e == ' ' || *e == '\t' || *e == '\n' || *e == '\r');
        if (is_space == 0) {
            break;
        }
        e = e - 1;
    }

    t = e;
    while (t > s) {
        is_space = (*(t - 1) == ' ' || *(t - 1) == '\t' || *(t - 1) == '\n' || *(t - 1) == '\r');
        if (is_space != 0) {
            break;
        }
        t = t - 1;
    }

    if (t < s) {
        return 0;
    }

    val = 0;
    sign = 1;
    i = 0;
    if (*t == '-') {
        sign = -1;
        i = i + 1;
    }
    while (t + i <= e) {
        is_digit = (*(t + i) >= '0' && *(t + i) <= '9');
        if (is_digit == 0) {
            break;
        }
        val = val * 10 + (*(t + i) - '0');
        i = i + 1;
    }
    a = val * sign;
    e = t + i - 1;

    if (e < t) {
        if (*t == '+') {
            b = get(s, t, &t);
            a = get(s, t, &t);
            a = a + b;
        } else if (*t == '-') {
            b = get(s, t, &t);
            a = get(s, t, &t);
            a = a - b;
        } else if (*t == '*') {
            b = get(s, t, &t);
            a = get(s, t, &t);
            a = a * b;
        } else if (*t == '/') {
            b = get(s, t, &t);
            a = get(s, t, &t);
            a = a / b;
        } else if (*t == '^') {
            b = get(s, t, &t);
            a = get(s, t, &t);
            val = 1;
            for (i = 0; i < b; i = i + 1) {
                val = val * a;
            }
            a = val;
        } else {
            return 0;
        }
    }

    *new_e = t;
    return a;
}

int rpn(const char* s) {
    const char* e;
    int v;
    int is_space;
    int len;
    int i;

    len = 0;
    while (s[len] != '\0') {
        len = len + 1;
    }
    e = s + len;

    v = get(s, e, &e);

    while (e > s) {
        is_space = (*(e - 1) == ' ' || *(e - 1) == '\t' || *(e - 1) == '\n' || *(e - 1) == '\r');
        if (is_space == 0) {
            break;
        }
        e = e - 1;
    }

    if (e == s) {
        return v;
    }

    return 0;
}
