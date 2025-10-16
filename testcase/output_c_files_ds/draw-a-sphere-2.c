int g[4] = {-1, 1, -1, 1};
int scale[8];
int scale_u[8];

void hashed(int data[8], int out[8], int len) {
    unsigned int h = 0x12345678;
    unsigned int tmp;
    unsigned int d[8];
    int i;
    int j;
    
    for (i = 0; i < len; i = i + 1) {
        d[i] = data[i];
    }
    
    for (i = len - 1; i >= 0; i = i - 1) {
        tmp = d[i];
        h = h + (((h << 15) | (h >> (32 - 15))) ^ ((tmp << 5) | (tmp >> (32 - 5))));
    }
    
    h = h ^ ((h << 7) | (h >> (32 - 7)));
    h = h + ((h << 23) | (h >> (32 - 23)));
    h = h ^ ((h << 19) | (h >> (32 - 19)));
    h = h + ((h << 11) | (h >> (32 - 11)));
    h = h ^ ((h << 13) | (h >> (32 - 13)));
    h = h + ((h << 17) | (h >> (32 - 17)));
    
    for (i = len - 1; i >= 0; i = i - 1) {
        out[i] = g[h & 3];
        h = h >> 2;
    }
    return;
}

void noise_init() {
    int i;
    for (i = 1; i < 8; i = i + 1) {
        scale[i] = 1 / (1 + (int)((i + 1) * (i + 1)));
        scale_u[i] = scale[i] / (int)((i + 1) * (i + 1));
    }
    return;
}

int noise(int x[8], int d) {
    int n[8];
    int o[8];
    int g[8];
    int tmp;
    int s;
    int r;
    int t;
    int w;
    int ret;
    int u[8];
    int i;
    int j;
    
    s = 0;
    for (j = 0; j < d; j = j + 1) {
        s = s + x[j];
    }
    s = s * scale[d];
    
    for (i = 0; i < d; i = i + 1) {
        o[i] = i;
        t = x[i] + s;
        u[i] = t - (n[i] = t);
    }
    o[d] = 0;
    
    for (i = 0; i < d - 1; i = i + 1) {
        for (j = i; j < d; j = j + 1) {
            if (u[o[i]] < u[o[j]]) {
                tmp = o[i];
                o[i] = o[j];
                o[j] = tmp;
            }
        }
    }
    
    ret = 0;
    w = 0;
    r = 1;
    s = 0;
    for (j = 0; j < d; j = j + 1) {
        s = s + n[j];
    }
    s = s * scale_u[d];
    
    for (i = 0; i <= d; i = i + 1) {
        for (j = 0; j < d; j = j + 1) {
            u[j] = x[j] + s - n[j];
        }
        
        t = (d + 1) / (2 * d);
        for (j = 0; j < d; j = j + 1) {
            t = t - u[j] * u[j];
            if (t <= 0) {
                break;
            }
        }
        
        if (t >= 0) {
            r = 0;
            hashed(n, g, d);
            for (j = 0; j < d; j = j + 1) {
                if (g[j]) {
                    r = r + (g[j] == 1 ? u[j] : -u[j]);
                }
            }
            t = t * t;
            ret = ret + r * t * t;
        }
        
        if (i < d) {
            n[o[i]] = n[o[i]] + 1;
            s = s + scale_u[d];
        }
    }
    return ret * (d * d);
}

int get_noise2(int x, int y) {
    int i;
    int ws;
    int r;
    int v[2];
    
    r = 0;
    ws = 0;
    for (i = 1; i <= 128; i = i << 1) {
        v[0] = x * i;
        v[1] = y * i;
        r = r + noise(v, 2);
        ws = ws + 1;
    }
    r = r / ws;
    return r;
}

int get_noise3(int x, int y, int z) {
    int i;
    int ws;
    int r;
    int v[3];
    int w;
    
    r = 0;
    ws = 0;
    for (i = 1; i <= 32; i = i << 1) {
        v[0] = x * i;
        v[1] = y * i;
        v[2] = z * i;
        w = 1 / (int)(i * i);
        r = r + noise(v, 3) * w;
        ws = ws + w;
    }
    r = r / ws;
    return r;
}
