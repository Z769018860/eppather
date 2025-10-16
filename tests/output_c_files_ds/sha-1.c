unsigned char* sha1_hash(const unsigned char* string, int length) {
    int i;
    int j;
    unsigned char result[20];
    unsigned int h0 = 0x67452301;
    unsigned int h1 = 0xEFCDAB89;
    unsigned int h2 = 0x98BADCFE;
    unsigned int h3 = 0x10325476;
    unsigned int h4 = 0xC3D2E1F0;
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    unsigned int e;
    unsigned int f;
    unsigned int k;
    unsigned int temp;
    unsigned int w[80];
    unsigned int extended_length;
    unsigned int original_length;
    unsigned char* padded;
    int padding_length;
    
    original_length = length;
    padding_length = 56 - (length % 64);
    if (padding_length < 0) {
        padding_length = padding_length + 64;
    }
    extended_length = length + padding_length + 8;
    padded = (unsigned char*)malloc(extended_length);
    for (i = 0; i < length; i = i + 1) {
        padded[i] = string[i];
    }
    padded[length] = 0x80;
    for (i = length + 1; i < length + padding_length; i = i + 1) {
        padded[i] = 0x00;
    }
    original_length = original_length * 8;
    for (i = 0; i < 8; i = i + 1) {
        padded[length + padding_length + i] = (original_length >> (56 - i * 8)) & 0xFF;
    }
    for (i = 0; i < extended_length / 64; i = i + 1) {
        for (j = 0; j < 16; j = j + 1) {
            w[j] = (padded[i * 64 + j * 4] << 24) | (padded[i * 64 + j * 4 + 1] << 16) | (padded[i * 64 + j * 4 + 2] << 8) | padded[i * 64 + j * 4 + 3];
        }
        for (j = 16; j < 80; j = j + 1) {
            w[j] = (w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16]);
            w[j] = (w[j] << 1) | (w[j] >> 31);
        }
        a = h0;
        b = h1;
        c = h2;
        d = h3;
        e = h4;
        for (j = 0; j < 80; j = j + 1) {
            if (j < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }
            temp = ((a << 5) | (a >> 27)) + f + e + k + w[j];
            e = d;
            d = c;
            c = (b << 30) | (b >> 2);
            b = a;
            a = temp;
        }
        h0 = h0 + a;
        h1 = h1 + b;
        h2 = h2 + c;
        h3 = h3 + d;
        h4 = h4 + e;
    }
    result[0] = (h0 >> 24) & 0xFF;
    result[1] = (h0 >> 16) & 0xFF;
    result[2] = (h0 >> 8) & 0xFF;
    result[3] = h0 & 0xFF;
    result[4] = (h1 >> 24) & 0xFF;
    result[5] = (h1 >> 16) & 0xFF;
    result[6] = (h1 >> 8) & 0xFF;
    result[7] = h1 & 0xFF;
    result[8] = (h2 >> 24) & 0xFF;
    result[9] = (h2 >> 16) & 0xFF;
    result[10] = (h2 >> 8) & 0xFF;
    result[11] = h2 & 0xFF;
    result[12] = (h3 >> 24) & 0xFF;
    result[13] = (h3 >> 16) & 0xFF;
    result[14] = (h3 >> 8) & 0xFF;
    result[15] = h3 & 0xFF;
    result[16] = (h4 >> 24) & 0xFF;
    result[17] = (h4 >> 16) & 0xFF;
    result[18] = (h4 >> 8) & 0xFF;
    result[19] = h4 & 0xFF;
    return result;
}
