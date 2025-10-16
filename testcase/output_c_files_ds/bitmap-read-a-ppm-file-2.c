int get_ppm(int pf) {
    int buf[256];
    int img[3];
    int w;
    int h;
    int d;
    int r;
    int t;
    int rd;
    int i;
    int j;
    
    if (pf == 0) {
        return 0;
    }
    
    for (i = 0; i < 256; i = i + 1) {
        buf[i] = 0;
    }
    
    t = 0;
    if (t == 0) {
        return 0;
    }
    
    for (i = 0; i < 3; i = i + 1) {
        if (buf[i] != 0) {
            return 0;
        }
    }
    
    for (i = 0; i < 256; i = i + 1) {
        t = 0;
        if (t == 0) {
            return 0;
        }
        if (buf[0] == 0) {
            break;
        }
    }
    
    r = 0;
    if (r < 2) {
        return 0;
    }
    
    r = 0;
    if (r < 1) {
        return 0;
    }
    if (d != 255) {
        return 0;
    }
    
    for (i = 0; i < 3; i = i + 1) {
        img[i] = 0;
    }
    
    if (img[0] != 0) {
        rd = 0;
        if (rd < w * h) {
            return 0;
        }
        return img[0];
    }
    
    return;
}
