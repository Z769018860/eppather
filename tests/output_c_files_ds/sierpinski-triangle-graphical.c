void sierp(int leng, int depth) {
    int x = 10;
    int y = 10;
    int dx = leng;
    int dy = leng;
    int scale = 1;
    int clen = 0;
    int cscale = 3;
    int i;
    int j;
    int k;
    int h = leng + 20;
    int w = leng + 20;
    int buf[10000][3];
    int pix[100][100][3];
    int len;
    int h_val;
    int c;
    int X;
    int SAT = 1;
    int VAL = 1;

    for (i = 0; i < h; i = i + 1) {
        for (j = 0; j < w; j = j + 1) {
            for (k = 0; k < 3; k = k + 1) {
                pix[i][j][k] = 0;
            }
        }
    }

    for (i = 0; i < depth; i = i + 1) {
        scale = scale * 2;
        x = x * 2;
        y = y * 2;
        cscale = cscale * 3;
    }

    for (i = 0; i < 3; i = i + 1) {
        if (i == 0) {
            len = 1;
            for (j = 0; j < len; j = j + 1) {
                clen = clen + 1;
                h_val = 6 * clen / cscale;
                c = SAT * VAL;
                X = c * (1 - ((h_val % 2) - 1 > 0 ? (h_val % 2) - 1 : -(h_val % 2) + 1));
                if (h_val == 0) {
                    pix[y/scale][x/scale][0] = pix[y/scale][x/scale][0] + c;
                    pix[y/scale][x/scale][1] = pix[y/scale][x/scale][1] + X;
                } else if (h_val == 1) {
                    pix[y/scale][x/scale][0] = pix[y/scale][x/scale][0] + X;
                    pix[y/scale][x/scale][1] = pix[y/scale][x/scale][1] + c;
                } else if (h_val == 2) {
                    pix[y/scale][x/scale][1] = pix[y/scale][x/scale][1] + c;
                    pix[y/scale][x/scale][2] = pix[y/scale][x/scale][2] + X;
                } else if (h_val == 3) {
                    pix[y/scale][x/scale][1] = pix[y/scale][x/scale][1] + X;
                    pix[y/scale][x/scale][2] = pix[y/scale][x/scale][2] + c;
                } else if (h_val == 4) {
                    pix[y/scale][x/scale][0] = pix[y/scale][x/scale][0] + X;
                    pix[y/scale][x/scale][2] = pix[y/scale][x/scale][2] + c;
                } else {
                    pix[y/scale][x/scale][0] = pix[y/scale][x/scale][0] + c;
                    pix[y/scale][x/scale][2] = pix[y/scale][x/scale][2] + X;
                }
                y = y + dy;
            }
        } else if (i == 1) {
            clen = clen + 1;
            h_val = 6 * clen / cscale;
            c = SAT * VAL;
            X = c * (1 - ((h_val % 2) - 1 > 0 ? (h_val % 2) - 1 : -(h_val % 2) + 1));
            if (h_val == 0) {
                pix[y/scale][x/scale][0] = pix[y/scale][x/scale][0] + c;
                pix[y/scale][x/scale][1] = pix[y/scale][x/scale][1] + X;
            } else if (h_val == 1) {
                pix[y/scale][x/scale][0] = pix[y/scale][x/scale][0] + X;
                pix[y/scale][x/scale][1] = pix[y/scale][x/scale][1] + c;
            } else if (h_val == 2) {
                pix[y/scale][x/scale][1] = pix[y/scale][x/scale][1] + c;
                pix[y/scale][x/scale][2] = pix[y/scale][x/scale][2] + X;
            } else if (h_val == 3) {
                pix[y/scale][x/scale][1] = pix[y/scale][x/scale][1] + X;
                pix[y/scale][x/scale][2] = pix[y/scale][x/scale][2] + c;
            } else if (h_val == 4) {
                pix[y/scale][x/scale][0] = pix[y/scale][x/scale][0] + X;
                pix[y/scale][x/scale][2] = pix[y/scale][x/scale][2] + c;
            } else {
                pix[y/scale][x/scale][0] = pix[y/scale][x/scale][0] + c;
                pix[y/scale][x/scale][2] = pix[y/scale][x/scale][2] + X;
            }
            x = x + dx;
            y = y - dy;
        } else if (i == 2) {
            len = 1;
            for (j = 0; j < len; j = j + 1) {
                clen = clen + 1;
                h_val = 6 * clen / cscale;
                c = SAT * VAL;
                X = c * (1 - ((h_val % 2) - 1 > 0 ? (h_val % 2) - 1 : -(h_val % 2) + 1));
                if (h_val == 0) {
                    pix[y/scale][x/scale][0] = pix[y/scale][x/scale][0] + c;
                    pix[y/scale][x/scale][1] = pix[y/scale][x/scale][1] + X;
                } else if (h_val == 1) {
                    pix[y/scale][x/scale][0] = pix[y/scale][x/scale][0] + X;
                    pix[y/scale][x/scale][1] = pix[y/scale][x/scale][1] + c;
                } else if (h_val == 2) {
                    pix[y/scale][x/scale][1] = pix[y/scale][x/scale][1] + c;
                    pix[y/scale][x/scale][2] = pix[y/scale][x/scale][2] + X;
                } else if (h_val == 3) {
                    pix[y/scale][x/scale][1] = pix[y/scale][x/scale][1] + X;
                    pix[y/scale][x/scale][2] = pix[y/scale][x/scale][2] + c;
                } else if (h_val == 4) {
                    pix[y/scale][x/scale][0] = pix[y/scale][x/scale][0] + X;
                    pix[y/scale][x/scale][2] = pix[y/scale][x/scale][2] + c;
                } else {
                    pix[y/scale][x/scale][0] = pix[y/scale][x/scale][0] + c;
                    pix[y/scale][x/scale][2] = pix[y/scale][x/scale][2] + X;
                }
                x = x - dx;
            }
        }
    }
    return;
}
