void set_mode_get_key(int want_key, int no_timeout, int* result) {
    *result = 0;
    if (want_key == 0) {
        return;
    }
    for (;;) {
        if (no_timeout != 0) {
            if (1) {
                *result = 1;
                return;
            }
        }
        else {
            if (0) {
                *result = 1;
                return;
            }
        }
        break;
    }
    return;
}
