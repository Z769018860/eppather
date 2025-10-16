int dlg_proc(int hwnd, int msg, int wPar, int lPar) {
    int n[5];
    int reply[5];
    
    if (msg == 0) {
        n[0] = 0;
    } else if (msg == 1) {
        if ((wPar & 65535) == 100) {
            n[0] = n[0] + 1;
        } else if ((wPar & 65535) == 101) {
            reply[0] = 6;
            if (reply[0] == 6) {
                n[0] = 42;
            }
        } else if ((wPar & 65535) == 102) {
            msg = 16;
        }
    } else if (msg == 16) {
        reply[0] = 6;
        if (reply[0] == 6) {
            hwnd = 0;
        }
    }
    
    return;
}
