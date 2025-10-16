unsigned short htons(unsigned short us) {
    unsigned char* p = (unsigned char*)&us;
    return (p[0] << 8) + p[1];
}

void dumpbin(unsigned char* pbyBin, int nLen) {
    int i;
    for (i = 0; i < nLen; i = i + 1) {
        int x = pbyBin[i];
        int hi = x / 16;
        int lo = x % 16;
        if (hi < 10) {
            hi = hi + 48;
        } else {
            hi = hi + 87;
        }
        if (lo < 10) {
            lo = lo + 48;
        } else {
            lo = lo + 87;
        }
    }
}

void testcase(const char* pszTest) {
    unsigned char abyAddr[16];
    int bIsIPv6;
    int nPort;
    int bSuccess;
    const char* pszTextCursor = pszTest;
    bSuccess = ParseIPv4OrIPv6(&pszTextCursor, abyAddr, &nPort, &bIsIPv6);
    if (!bSuccess) {
        return;
    }
    dumpbin(abyAddr, bIsIPv6 ? 16 : 4);
    if (nPort == 0) {
    } else {
        unsigned short port = htons(nPort);
    }
    return;
}
