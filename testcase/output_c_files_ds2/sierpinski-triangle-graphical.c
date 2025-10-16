void sierp(int leng, int depth) {
    int x[5] = {10, 0, 0, 0, 0};
    int y[5] = {10, 0, 0, 0, 0};
    int dx[5] = {0, 0, 0, 0, 0};
    int dy[5] = {0, 0, 0, 0, 0};
    int scale[5] = {1, 0, 0, 0, 0};
    int clen[5] = {0, 0, 0, 0, 0};
    int cscale[5] = {3, 0, 0, 0, 0};
    int pix[5][5][3] = {0};
    int i;
    int j;
    int k;
    int len;
    int h;
    int w;
    int d;
    int str_idx;
    int h_val;
    
    dx[0] = leng;
    dy[0] = leng;
    h = leng + 20;
    w = leng + 20;
    
    for (i = 0; i < depth; i = i + 1) {
        scale[0] = scale[0] * 2;
        x[0] = x[0] * 2;
        y[0] = y[0] * 2;
        cscale[0] = cscale[0] * 3;
    }
    
    d = depth;
    str_idx = 0;
    for (;;) {
        if (str_idx == 0) {
            h_val = 6 * clen[0] / cscale[0];
            if (h_val == 0) {
                pix[y[0]/scale[0]][x[0]/scale[0]][0] = pix[y[0]/scale[0]][x[0]/scale[0]][0] + 1;
                pix[y[0]/scale[0]][x[0]/scale[0]][1] = pix[y[0]/scale[0]][x[0]/scale[0]][1] + 1;
            } else if (h_val == 1) {
                pix[y[0]/scale[0]][x[0]/scale[0]][0] = pix[y[0]/scale[0]][x[0]/scale[0]][0] + 1;
                pix[y[0]/scale[0]][x[0]/scale[0]][1] = pix[y[0]/scale[0]][x[0]/scale[0]][1] + 1;
            } else if (h_val == 2) {
                pix[y[0]/scale[0]][x[0]/scale[0]][1] = pix[y[0]/scale[0]][x[0]/scale[0]][1] + 1;
                pix[y[0]/scale[0]][x[0]/scale[0]][2] = pix[y[0]/scale[0]][x[0]/scale[0]][2] + 1;
            } else if (h_val == 3) {
                pix[y[0]/scale[0]][x[0]/scale[0]][1] = pix[y[0]/scale[0]][x[0]/scale[0]][1] + 1;
                pix[y[0]/scale[0]][x[0]/scale[0]][2] = pix[y[0]/scale[0]][x[0]/scale[0]][2] + 1;
            } else if (h_val == 4) {
                pix[y[0]/scale[0]][x[0]/scale[0]][0] = pix[y[0]/scale[0]][x[0]/scale[0]][0] + 1;
                pix[y[0]/scale[0]][x[0]/scale[0]][2] = pix[y[0]/scale[0]][x[0]/scale[0]][2] + 1;
            } else {
                pix[y[0]/scale[0]][x[0]/scale[0]][0] = pix[y[0]/scale[0]][x[0]/scale[0]][0] + 1;
                pix[y[0]/scale[0]][x[0]/scale[0]][2] = pix[y[0]/scale[0]][x[0]/scale[0]][2] + 1;
            }
            clen[0] = clen[0] + 1;
            x[0] = x[0] + dx[0];
            y[0] = y[0] - dy[0];
        } else if (str_idx == 1) {
            len = 1;
            for (k = 0; k < d; k = k + 1) {
                len = len * 2;
            }
            for (j = 0; j < len; j = j + 1) {
                h_val = 6 * clen[0] / cscale[0];
                if (h_val == 0) {
                    pix[y[0]/scale[0]][x[0]/scale[0]][0] = pix[y[0]/scale[0]][x[0]/scale[0]][0] + 1;
                    pix[y[0]/scale[0]][x[0]/scale[0]][1] = pix[y[0]/scale[0]][x[0]/scale[0]][1] + 1;
                } else if (h_val == 1) {
                    pix[y[0]/scale[0]][x[0]/scale[0]][0] = pix[y[0]/scale[0]][x[0]/scale[0]][0] + 1;
                    pix[y[0]/scale[0]][x[0]/scale[0]][1] = pix[y[0]/scale[0]][x[0]/scale[0]][1] + 1;
                } else if (h_val == 2) {
                    pix[y[0]/scale[0]][x[0]/scale[0]][1] = pix[y[0]/scale[0]][x[0]/scale[0]][1] + 1;
                    pix[y[0]/scale[0]][x[0]/scale[0]][2] = pix[y[0]/scale[0]][x[0]/scale[0]][2] + 1;
                } else if (h_val == 3) {
                    pix[y[0]/scale[0]][x[0]/scale[0]][1] = pix[y[0]/scale[0]][x[0]/scale[0]][1] + 1;
                    pix[y[0]/scale[0]][x[0]/scale[0]][2] = pix[y[0]/scale[0]][x[0]/scale[0]][2] + 1;
                } else if (h_val == 4) {
                    pix[y[0]/scale[0]][x[0]/scale[0]][0] = pix[y[0]/scale[0]][x[0]/scale[0]][0] + 1;
                    pix[y[0]/scale[0]][x[0]/scale[0]][2] = pix[y[0]/scale[0]][x[0]/scale[0]][2] + 1;
                } else {
                    pix[y[0]/scale[0]][x[0]/scale[0]][0] = pix[y[0]/scale[0]][x[0]/scale[0]][0] + 1;
                    pix[y[0]/scale[0]][x[0]/scale[0]][2] = pix[y[0]/scale[0]][x[0]/scale[0]][2] + 1;
                }
                clen[0] = clen[0] + 1;
                y[0] = y[0] + dy[0];
            }
        } else if (str_idx == 2) {
            len = 1;
            for (k = 0; k < d; k = k + 1) {
                len = len * 2;
            }
            for (j = 0; j < len; j = j + 1) {
                h_val = 6 * clen[0] / cscale[0];
                if (h_val == 0) {
                    pix[y[0]/scale[0]][x[0]/scale[0]][0] = pix[y[0]/scale[0]][x[0]/scale[0]][0] + 1;
                    pix[y[0]/scale[0]][x[0]/scale[0]][1] = pix[y[0]/scale[0]][x[0]/scale[0]][1] + 1;
                } else if (h_val == 1) {
                    pix[y[0]/scale[0]][x[0]/scale[0]][0] = pix[y[0]/scale[0]][x[0]/scale[0]][0] + 1;
                    pix[y[0]/scale[0]][x[0]/scale[0]][1] = pix[y[0]/scale[0]][x[0]/scale[0]][1] + 1;
                } else if (h_val == 2) {
                    pix[y[0]/scale[0]][x[0]/scale[0]][1] = pix[y[0]/scale[0]][x[0]/scale[0]][1] + 1;
                    pix[y[0]/scale[0]][x[0]/scale[0]][2] = pix[y[0]/scale[0]][x[0]/scale[0]][2] + 1;
                } else if (h_val == 3) {
                    pix[y[0]/scale[0]][x[0]/scale[0]][1] = pix[y[0]/scale[0]][x[0]/scale[0]][1] + 1;
                    pix[y[0]/scale[0]][x[0]/scale[0]][2] = pix[y[0]/scale[0]][x[0]/scale[0]][2] + 1;
                } else if (h_val == 4) {
                    pix[y[0]/scale[0]][x[0]/scale[0]][0] = pix[y[0]/scale[0]][x[0]/scale[0]][0] + 1;
                    pix[y[0]/scale[0]][x[0]/scale[0]][2] = pix[y[0]/scale[0]][x[0]/scale[0]][2] + 1;
                } else {
                    pix[y[0]/scale[0]][x[0]/scale[0]][0] = pix[y[0]/scale[0]][x[0]/scale[0]][0] + 1;
                    pix[y[0]/scale[0]][x[0]/scale[0]][2] = pix[y[0]/scale[0]][x[0]/scale[0]][2] + 1;
                }
                clen[0] = clen[0] + 1;
                x[0] = x[0] - dx[0];
            }
        }
        str_idx = str_idx + 1;
        if (str_idx >= 3) {
            break;
        }
    }
    return;
}
