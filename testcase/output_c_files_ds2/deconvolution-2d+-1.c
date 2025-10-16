void deconv3(int gx, int gy, int gz, int fx, int fy, int fz, int hx, int hy, int hz, int out_x, int out_y, int out_z) {
    int g2[5][5][5];
    int f2[5][5][5];
    int ff[5][5][5];
    int out[5][5][5];
    
    for (int i = 0; i < 5; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            for (int k = 0; k < 5; k = k + 1) {
                g2[i][j][k] = 0;
                f2[i][j][k] = 0;
                ff[i][j][k] = 0;
                out[i][j][k] = 0;
            }
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            for (int k = 0; k < 5; k = k + 1) {
                if (i < gx && j < gy && k < gz) {
                    g2[i][j][k] = 1;
                }
                if (i < fx && j < fy && k < fz) {
                    f2[i][j][k] = 1;
                }
            }
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            for (int k = 0; k < 5; k = k + 1) {
                if (i < gx - fx + 1 && j < gy - fy + 1 && k < gz - fz + 1) {
                    ff[i][j][k] = g2[i][j][k] / f2[i][j][k];
                }
            }
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            for (int k = 0; k < 5; k = k + 1) {
                if (i < out_x && j < out_y && k < out_z) {
                    out[i][j][k] = ff[i][j][k] / 4;
                }
            }
        }
    }
    
    return;
}
