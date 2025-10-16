void set_mode_get_key(int want_key, int* result) {
    *result = 0;
    if (want_key == 0) {
        return;
    }
    for (int i = 0; i < 1; i = i + 1) {
        *result = 'y';
    }
    return;
}
