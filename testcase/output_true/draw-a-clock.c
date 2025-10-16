void draw(int size) {
    int sx[3];
    int sy[3];
    int sw[3];
    int fade[3] = {100, 35, 35};
    int angle[3];
    int cx = size / 2;
    int x[5];
    int y[5];
    int pix[5];
    int k[5];
    int i[5];
    int j[5];
    int d[5];
    int l[5];
    
    sw[0] = size * 2 / 100;
    sw[1] = size * 3 / 100;
    sw[2] = size * 5 / 100;
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        angle[0] = i[0] * 314159265 / 30;
        sy[0] = -cx * 1000000 / 1000000 * angle[0];
        sx[0] = cx * 1000000 / 1000000 * angle[0];
        
        angle[1] = (i[0] + i[0] / 60) * 314159265 / 30;
        sy[1] = -cx * 800000 / 1000000 * angle[1];
        sx[1] = cx * 800000 / 1000000 * angle[1];
        
        angle[2] = (i[0] + i[0] / 60) * 314159265 / 6;
        sy[2] = -cx * 600000 / 1000000 * angle[2];
        sx[2] = cx * 600000 / 1000000 * angle[2];
        
        for (i[1] = 0; i[1] < 5; i[1] = i[1] + 1) {
            y[0] = i[1] - cx;
            for (j[0] = 0; j[0] < 5; j[0] = j[0] + 1) {
                x[0] = (j[0] - 2 * cx) / 2;
                pix[0] = 0;
                for (k[0] = 2; k[0] >= 0; k[0] = k[0] - 1) {
                    l[0] = (x[0] * sx[k[0]] + y[0] * sy[k[0]]) / (sx[k[0]] * sx[k[0]] + sy[k[0]] * sy[k[0]]);
                    if (l[0] > 1) {
                        x[1] = x[0] - sx[k[0]];
                        y[1] = y[0] - sy[k[0]];
                    } else {
                        if (l[0] >= 0) {
                            x[1] = x[0] - l[0] * sx[k[0]];
                            y[1] = y[0] - l[0] * sy[k[0]];
                        } else {
                            x[1] = x[0];
                            y[1] = y[0];
                        }
                    }
                    d[0] = x[1] * x[1] + y[1] * y[1];
                    if (d[0] < sw[k[0]] - 5) {
                        pix[1] = 10 * fade[k[0]] / 100;
                    } else {
                        if (d[0] < sw[k[0]] + 5) {
                            pix[1] = (5 + (sw[k[0]] - d[0]) * 10) * fade[k[0]] / 100;
                        } else {
                            pix[1] = 0;
                        }
                    }
                }
            }
        }
    }
    return;
}
