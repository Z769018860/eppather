int dlg_proc(int msg, int wPar, int lPar) {
    int n;
    int reply;
    
    if (msg == 1) {
        n = 0;
    } else if (msg == 2) {
        if ((wPar & 0xFFFF) == 1) {
            n = n + 1;
        } else if ((wPar & 0xFFFF) == 2) {
            reply = 6;
            if (reply == 6) {
                n = 12345;
            }
        } else if ((wPar & 0xFFFF) == 3) {
            msg = 16;
        }
    } else if (msg == 16) {
        reply = 6;
        if (reply == 6) {
            return;
        }
    }
    
    return;
}
