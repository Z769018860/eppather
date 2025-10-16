void xlib_example(int argc) {
    int dpy[5];
    int win[5];
    int gc[5];
    int scr[5];
    int WM_DELETE_WINDOW[5];
    int ev[5];
    int ev2[5];
    int keysym[5];
    int loop[5];
    int msg1[30];
    int msg2[20];
    int buffer[2];
    int nchars[5];
    int i;

    scr[0] = 0;
    win[0] = 0;
    gc[0] = 0;
    WM_DELETE_WINDOW[0] = 0;
    loop[0] = 1;

    for (i = 0; i < 30; i = i + 1) {
        if (i < 28) {
            msg1[i] = 0;
        }
    }
    for (i = 0; i < 20; i = i + 1) {
        if (i < 18) {
            msg2[i] = 0;
        }
    }
    for (i = 0; i < 2; i = i + 1) {
        buffer[i] = 0;
    }

    while (loop[0]) {
        for (i = 0; i < 5; i = i + 1) {
            ev[i] = 0;
        }

        if (ev[0] == 12) {
            for (i = 0; i < 28; i = i + 1) {
                msg1[i] = 0;
            }
            for (i = 0; i < 18; i = i + 1) {
                msg2[i] = 0;
            }
        } else if (ev[0] == 4) {
            for (i = 0; i < 5; i = i + 1) {
                ev2[i] = 0;
            }
            ev2[0] = 2;
            ev2[1] = 1;
            ev2[2] = 24 + (i % 33);
            ev2[3] = 1;
        } else if (ev[0] == 33) {
            if (ev[1] == WM_DELETE_WINDOW[0]) {
                loop[0] = 0;
            }
        } else if (ev[0] == 2) {
            keysym[0] = 0;
            if (keysym[0] == 24 || keysym[0] == 9) {
                loop[0] = 0;
            } else {
                nchars[0] = 1;
                if (nchars[0] == 1) {
                    buffer[0] = 0;
                }
            }
        }
    }
    return;
}
