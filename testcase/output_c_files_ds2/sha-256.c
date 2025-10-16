int sha256_hash(int input_len, char input[5], int output_len, unsigned char output[5]) {
    int i;
    int j;
    int k;
    int state[8];
    int w[64];
    int h0 = 1779033703;
    int h1 = 3144134277;
    int h2 = 1013904242;
    int h3 = 2773480762;
    int h4 = 1359893119;
    int h5 = 2600822924;
    int h6 = 528734635;
    int h7 = 1541459225;
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
    int t1;
    int t2;
    int m[16];
    
    for (i = 0; i < 5; i = i + 1) {
        m[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (i < input_len) {
            m[i / 4] = m[i / 4] | (input[i] << ((3 - (i % 4)) * 8));
        }
    }
    
    m[input_len / 4] = m[input_len / 4] | (128 << ((3 - (input_len % 4)) * 8));
    m[15] = input_len * 8;
    
    state[0] = h0;
    state[1] = h1;
    state[2] = h2;
    state[3] = h3;
    state[4] = h4;
    state[5] = h5;
    state[6] = h6;
    state[7] = h7;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 16; j = j + 1) {
            if (i * 16 + j < 16) {
                w[j] = m[i * 16 + j];
            } else {
                w[j] = 0;
            }
        }
        
        for (j = 16; j < 64; j = j + 1) {
            w[j] = 0;
        }
        
        a = state[0];
        b = state[1];
        c = state[2];
        d = state[3];
        e = state[4];
        f = state[5];
        g = state[6];
        h = state[7];
        
        for (j = 0; j < 64; j = j + 1) {
            t1 = h + ((e >> 6) | (e << 26)) + ((e >> 11) | (e << 21)) + ((e >> 25) | (e << 7)) + (g ^ (e & (f ^ g))) + 0x428a2f98 + w[j];
            t2 = ((a >> 2) | (a << 30)) + ((a >> 13) | (a << 19)) + ((a >> 22) | (a << 10)) + ((a & b) ^ (a & c) ^ (b & c));
            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }
        
        state[0] = state[0] + a;
        state[1] = state[1] + b;
        state[2] = state[2] + c;
        state[3] = state[3] + d;
        state[4] = state[4] + e;
        state[5] = state[5] + f;
        state[6] = state[6] + g;
        state[7] = state[7] + h;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 4; j = j + 1) {
            if (i * 4 + j < output_len) {
                output[i * 4 + j] = (state[i] >> ((3 - j) * 8)) & 255;
            }
        }
    }
    
    return;
}
