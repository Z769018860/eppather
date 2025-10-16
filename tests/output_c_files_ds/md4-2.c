unsigned char* MD4(const char* message, unsigned int length) {
    unsigned int A = 0x67452301;
    unsigned int B = 0xEFCDAB89;
    unsigned int C = 0x98BADCFE;
    unsigned int D = 0x10325476;
    unsigned int X[16];
    unsigned int AA;
    unsigned int BB;
    unsigned int CC;
    unsigned int DD;
    unsigned int i;
    unsigned int j;
    unsigned int k;
    unsigned int l;
    unsigned int temp;
    unsigned char* result = (unsigned char*)malloc(16);
    
    for (i = 0; i < 16; i = i + 1) {
        X[i] = 0;
    }
    
    for (i = 0; i < length; i = i + 1) {
        X[i >> 2] = X[i >> 2] | ((unsigned int)(message[i]) << ((i % 4) * 8));
    }
    
    X[length >> 2] = X[length >> 2] | (0x80 << ((length % 4) * 8));
    X[14] = length * 8;
    
    AA = A;
    BB = B;
    CC = C;
    DD = D;
    
    for (i = 0; i < 16; i = i + 1) {
        temp = A + ((B & C) | ((~B) & D)) + X[i];
        A = D;
        D = C;
        C = B;
        B = B + ((temp << 3) | (temp >> 29));
    }
    
    for (i = 0; i < 16; i = i + 1) {
        temp = A + ((B & C) | (B & D) | (C & D)) + X[(i % 4) * 4 + (i / 4)] + 0x5A827999;
        A = D;
        D = C;
        C = B;
        B = B + ((temp << 5) | (temp >> 27));
    }
    
    for (i = 0; i < 16; i = i + 1) {
        temp = A + (B ^ C ^ D) + X[(i % 8) * 2 + (i / 8)] + 0x6ED9EBA1;
        A = D;
        D = C;
        C = B;
        B = B + ((temp << 9) | (temp >> 23));
    }
    
    A = A + AA;
    B = B + BB;
    C = C + CC;
    D = D + DD;
    
    for (i = 0; i < 4; i = i + 1) {
        result[i] = (A >> (i * 8)) & 0xFF;
        result[i + 4] = (B >> (i * 8)) & 0xFF;
        result[i + 8] = (C >> (i * 8)) & 0xFF;
        result[i + 12] = (D >> (i * 8)) & 0xFF;
    }
    
    return result;
}
