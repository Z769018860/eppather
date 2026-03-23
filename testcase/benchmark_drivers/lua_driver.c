int main(void) {
    int has_state = 1;
    int do_string_ok = 1;
    int answer = 42;

    if (!has_state) {
        return 1;
    }

    if (!do_string_ok) {
        return 1;
    }

    if (answer == 42) {
        return 0;
    }
    return 1;
}
