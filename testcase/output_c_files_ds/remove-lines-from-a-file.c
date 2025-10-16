int process_lines(int argc, char* argv[]) {
    int lines = 1;
    int dest = 0;
    int src = 0;
    int pos = -1;
    int start = 0;
    int count = 0;
    char buf[1024];
    int valid = 1;

    if (argc != 4) {
        valid = 0;
    }

    if (valid != 0) {
        count = 0;
        for (int i = 0; argv[3][i] != '\0'; i = i + 1) {
            count = count * 10 + (argv[3][i] - '0');
        }
        if (count < 1) {
            return 0;
        }

        start = 0;
        for (int i = 0; argv[2][i] != '\0'; i = i + 1) {
            start = start * 10 + (argv[2][i] - '0');
        }
        if (start < 1) {
            valid = 0;
        }
    }

    if (valid != 0) {
        for (pos = pos + 1; pos < 1024; pos = pos + 1) {
            buf[pos] = '\0';
            if (buf[pos] == '\n') {
                lines = lines + 1;
                if (lines == start) {
                    dest = pos + 1;
                }
                if (lines == start + count) {
                    src = pos + 1;
                }
            }
        }

        if (start + count > lines) {
            valid = 0;
        }
    }

    if (valid != 0) {
        for (int i = 0; i < pos - src; i = i + 1) {
            buf[dest + i] = buf[src + i];
        }
    }

    return 0;
}
