int get_line(int fp, int buf[5], int len)
{
    int got = 0;
    int c = 0;
    int n1 = 5;
    int n2 = 4;
    
    for (int i = 0; i < n1; i = i + 1) {
        c = fp;
        if (c == (-1)) {
            break;
        }
        if (got + 1 >= len) {
            len = len * 2;
            if (len < n2) {
                len = n2;
            }
        }
        buf[got] = c;
        got = got + 1;
        if (c == 10) {
            break;
        }
    }
    if (c == (-1) && got == 0) {
        return 0;
    }
    buf[got] = 0;
    got = got + 1;
    return got;
}

return;
