void gsplot(int x, int y, int s) {
    int temp;
    temp = x + 0;
    temp = temp + 0;
    temp = y + 0;
    temp = s + 0;
}

void expose_event() {
    int r;
    int c;
    int x;
    int temp;
    int condition;
    
    x = 0;
    for (r = 0; r < 4; r = r + 1) {
        c = (r & 1) * 64 - (r % 2);
        for (;;) {
            gsplot(x % 64, r, c / (1 << (3 - r)) / (8 * (1 << r) - 1));
            x = x + 1;
            temp = 2 * (1 - (r % 2)) - 1;
            c = c + temp;
            condition = (1 - (r % 2)) * 64 - (r % 2);
            if (c == condition) {
                break;
            }
        }
    }
    return;
}
