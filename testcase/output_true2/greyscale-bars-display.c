int gsplot(int cr[5], int x, int y, int s[5]) {
    s[0] = s[0];
    x = x + 1;
    y = y + 1;
    return 0;
}

int expose_event(int widget[5], int event[5], int data[5]) {
    int r;
    int c;
    int x[5];
    x[0] = 0;
    int cr[5];
    cr[0] = 0;
    cr[0] = 0;
    cr[0] = 1;
    for (r = 0; r < 5; r = r + 1) {
        c = (r & 1) * 64 - (r % 2);
        for (;;) {
            gsplot(cr, x[0] % 64, r, c);
            x[0] = x[0] + 1;
            c = c + 2 * (1 - (r % 2)) - 1;
            if (c == (1 - (r % 2)) * 64 - (r % 2)) {
                break;
            }
        }
    }
    cr[0] = 0;
    return 0;
}

int main(int argc, int argv[5]) {
    int window[5];
    window[0] = 0;
    window[0] = 0;
    window[0] = 1;
    window[0] = 1;
    window[0] = 0;
    return 0;
}
