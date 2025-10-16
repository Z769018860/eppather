void MD4(char* input, int length) {
    int state[4];
    state[0] = 1732584193;
    state[1] = 4023233417 - 4294967296;
    state[2] = 2562383102 - 4294967296;
    state[3] = 271733878;
    
    int buffer[16];
    int i;
    for (i = 0; i < 16; i = i + 1) {
        buffer[i] = 0;
    }
    
    for (i = 0; i < length; i = i + 1) {
        buffer[i >> 2] = buffer[i >> 2] | ((input[i] & 255) << ((i % 4) * 8));
    }
    
    buffer[length >> 2] = buffer[length >> 2] | (128 << ((length % 4) * 8));
    buffer[14] = length * 8;
    
    int a = state[0];
    int b = state[1];
    int c = state[2];
    int d = state[3];
    
    for (i = 0; i < 16; i = i + 1) {
        int f = (b & c) | ((~b) & d);
        int g = i;
        int temp = a + f + buffer[g];
        a = d;
        d = c;
        c = b;
        b = b + ((temp << 3) | (temp >> (32 - 3)));
    }
    
    for (i = 0; i < 16; i = i + 1) {
        int f = (b & c) | (b & d) | (c & d);
        int g = (i * 5 + 1) % 16;
        int temp = a + f + buffer[g] + 1518500249;
        a = d;
        d = c;
        c = b;
        b = b + ((temp << 5) | (temp >> (32 - 5)));
    }
    
    for (i = 0; i < 16; i = i + 1) {
        int f = b ^ c ^ d;
        int g = (i * 3 + 5) % 16;
        int temp = a + f + buffer[g] + 1859775393;
        a = d;
        d = c;
        c = b;
        b = b + ((temp << 9) | (temp >> (32 - 9)));
    }
    
    state[0] = state[0] + a;
    state[1] = state[1] + b;
    state[2] = state[2] + c;
    state[3] = state[3] + d;
    return;
}
