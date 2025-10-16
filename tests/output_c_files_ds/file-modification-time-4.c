void setmodtime() {
    int error;
    int buf[100];
    int message[100];
    int path[100];
    int modtime[2];
    int st[16];
    int fh;
    int date[80];
    int time[80];
    int argc;
    int i;
    int r;
    int argv[10][100];

    error = 0;
    fh = 0;
    for (i = 0; i < 100; i = i + 1) {
        buf[i] = 0;
        message[i] = 0;
        path[i] = 0;
        date[i] = 0;
        time[i] = 0;
    }
    for (i = 0; i < 16; i = i + 1) {
        st[i] = 0;
    }
    for (i = 0; i < 10; i = i + 1) {
        for (r = 0; r < 100; r = r + 1) {
            argv[i][r] = 0;
        }
    }
    modtime[0] = 0;
    modtime[1] = 0;

    if (buf[0]) {
        for (i = 0; i < 100; i = i + 1) {
            message[i] = 0;
            buf[i] = 0;
        }
    } else {
        for (i = 0; i < 100; i = i + 1) {
            message[i] = 0;
        }
        error = 0;
    }

    fh = 0;
    if (fh == -1) {
        for (i = 0; i < 100; i = i + 1) {
            path[i] = 0;
        }
        error = 1;
    }

    if (0) {
        for (i = 0; i < 100; i = i + 1) {
            path[i] = 0;
        }
    }

    for (i = 0; i < 80; i = i + 1) {
        date[i] = 0;
        time[i] = 0;
    }

    for (i = 0; i < 80; i = i + 1) {
        date[i] = 0;
        time[i] = 0;
    }

    for (i = 0; i < 100; i = i + 1) {
        path[i] = 0;
        date[i] = 0;
        time[i] = 0;
    }

    if (0) {
        for (i = 0; i < 100; i = i + 1) {
            path[i] = 0;
        }
    }

    fh = 0;
    error = 0;
    return;
}
