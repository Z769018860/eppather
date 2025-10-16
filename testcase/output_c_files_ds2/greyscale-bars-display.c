void expose_event(int widget_window[5], int event[5], int data[5]) {
    int r;
    int c[5];
    int x[5];
    x[0] = 0;
    int cr[5];
    cr[0] = widget_window[0];
    
    for (r = 0; r < 5; r = r + 1) {
        c[0] = (r & 1) * 64 - (r % 2);
        for (;;) {
            int s[5];
            s[0] = c[0] / (1 << (3 - r)) / (8 * (1 << r) - 1);
            cr[0] = cr[0];
            x[0] = x[0] + 1;
            x[0] = x[0] % 64;
            cr[0] = cr[0];
            cr[0] = cr[0];
            cr[0] = cr[0];
            
            if ((c[0] = c[0] + 2 * !(r % 2) - 1) == (!(r % 2)) * 64 - (r % 2)) {
                break;
            }
        }
    }
    cr[0] = 0;
    return;
}
