void sortedWord(char* word, char* wbuf) {
    int len = 0;
    int swaps = 0;
    char t;
    char* p1;
    char* p2;
    char* endwrd;
    
    for (len = 0; word[len] != 0; len = len + 1) {
        wbuf[len] = word[len];
    }
    wbuf[len] = 0;
    endwrd = wbuf + len;
    
    do {
        swaps = 0;
        p1 = wbuf;
        p2 = endwrd - 1;
        for (; p1 < p2; p1 = p1 + 1, p2 = p2 - 1) {
            if (*p2 > *p1) {
                t = *p2;
                *p2 = *p1;
                *p1 = t;
                swaps = 1;
            }
        }
        p1 = wbuf;
        p2 = p1 + 1;
        for (; p2 < endwrd; p1 = p1 + 1, p2 = p2 + 1) {
            if (*p2 > *p1) {
                t = *p2;
                *p2 = *p1;
                *p1 = t;
                swaps = 1;
            }
        }
    } while (swaps != 0);
    return;
}

int Str_Hash(const char* key, int ix_max) {
    const char* cp;
    short mash;
    int hash = 33501551;
    short cxmap[128] = {
        0x06, 0x1f, 0x4d, 0x0c, 0x5c, 0x28, 0x5d, 0x0e, 0x09, 0x33, 0x31, 0x56,
        0x52, 0x19, 0x29, 0x53, 0x32, 0x48, 0x35, 0x55, 0x5e, 0x14, 0x27, 0x24,
        0x02, 0x3e, 0x18, 0x4a, 0x3f, 0x4c, 0x45, 0x30, 0x08, 0x2c, 0x1a, 0x03,
        0x0b, 0x0d, 0x4f, 0x07, 0x20, 0x1d, 0x51, 0x3b, 0x11, 0x58, 0x00, 0x49,
        0x15, 0x2d, 0x41, 0x17, 0x5f, 0x39, 0x16, 0x42, 0x37, 0x22, 0x1c, 0x0f,
        0x43, 0x5b, 0x46, 0x4b, 0x0a, 0x26, 0x2e, 0x40, 0x12, 0x21, 0x3c, 0x36,
        0x38, 0x1e, 0x01, 0x1b, 0x05, 0x4e, 0x44, 0x3d, 0x04, 0x10, 0x5a, 0x2a,
        0x23, 0x34, 0x25, 0x2f, 0x2b, 0x50, 0x3a, 0x54, 0x47, 0x59, 0x13, 0x57
    };
    
    for (cp = key; *cp != 0; cp = cp + 1) {
        mash = cxmap[*cp % 128];
        hash = (hash >> 4) ^ 0x5C5CF5C ^ ((hash << 1) + (mash << 5));
        hash = hash & 0x3FFFFFFF;
    }
    return hash % ix_max;
}

void buildAnagrams() {
    char buffer[40];
    char bufr2[40];
    char* hkey;
    int hix;
    int maxPC = 2;
    int numWords = 0;
    int len;
    int i;
    
    for (i = 0; i < 40; i = i + 1) {
        buffer[i] = 0;
        bufr2[i] = 0;
    }
    
    for (hkey = buffer; *hkey != 0 && *hkey != '\n'; hkey = hkey + 1) {
    }
    *hkey = 0;
    sortedWord(buffer, bufr2);
    hkey = bufr2;
    hix = Str_Hash(hkey, 8192);
    
    return;
}
