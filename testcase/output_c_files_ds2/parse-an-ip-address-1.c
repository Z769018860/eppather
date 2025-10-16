int ParseIPv4OrIPv6(const char** ppszText, unsigned char* abyAddr, int* pnPort, int* pbIsIPv6) {
    unsigned char abyAddrLocal[16];
    int bIsIPv6local = 0;
    int nVal;
    const char* pszTextBefore;
    unsigned char* pbyAddrCursor;
    int nIdx;
    int bIPv4Detected;
    unsigned char* pbyZerosLoc;
    int nHead;
    int nTail;
    int nZeros;
    unsigned short usPortNetwork;
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        if ((*ppszText)[i] == ':') {
            bIsIPv6local = 1;
            break;
        }
        if ((*ppszText)[i] == '.') {
            break;
        }
        if ((*ppszText)[i] == '[') {
            bIsIPv6local = 1;
            break;
        }
    }
    
    if (pbIsIPv6 != 0) {
        *pbIsIPv6 = bIsIPv6local;
    }
    
    if (abyAddr == 0) {
        for (i = 0; i < 16; i = i + 1) {
            abyAddrLocal[i] = 0;
        }
        pbyAddrCursor = abyAddrLocal;
    } else {
        pbyAddrCursor = abyAddr;
    }
    
    if (bIsIPv6local == 0) {
        pszTextBefore = *ppszText;
        nVal = 0;
        while ((*ppszText)[0] >= '0' && (*ppszText)[0] <= '9') {
            nVal = nVal * 10;
            nVal = nVal + (*ppszText)[0] - '0';
            *ppszText = *ppszText + 1;
        }
        if ((*ppszText)[0] != '.' || nVal > 255 || pszTextBefore == *ppszText) {
            return 0;
        }
        pbyAddrCursor[0] = (unsigned char)nVal;
        pbyAddrCursor = pbyAddrCursor + 1;
        *ppszText = *ppszText + 1;
        
        pszTextBefore = *ppszText;
        nVal = 0;
        while ((*ppszText)[0] >= '0' && (*ppszText)[0] <= '9') {
            nVal = nVal * 10;
            nVal = nVal + (*ppszText)[0] - '0';
            *ppszText = *ppszText + 1;
        }
        if ((*ppszText)[0] != '.' || nVal > 255 || pszTextBefore == *ppszText) {
            return 0;
        }
        pbyAddrCursor[0] = (unsigned char)nVal;
        pbyAddrCursor = pbyAddrCursor + 1;
        *ppszText = *ppszText + 1;
        
        pszTextBefore = *ppszText;
        nVal = 0;
        while ((*ppszText)[0] >= '0' && (*ppszText)[0] <= '9') {
            nVal = nVal * 10;
            nVal = nVal + (*ppszText)[0] - '0';
            *ppszText = *ppszText + 1;
        }
        if ((*ppszText)[0] != '.' || nVal > 255 || pszTextBefore == *ppszText) {
            return 0;
        }
        pbyAddrCursor[0] = (unsigned char)nVal;
        pbyAddrCursor = pbyAddrCursor + 1;
        *ppszText = *ppszText + 1;
        
        pszTextBefore = *ppszText;
        nVal = 0;
        while ((*ppszText)[0] >= '0' && (*ppszText)[0] <= '9') {
            nVal = nVal * 10;
            nVal = nVal + (*ppszText)[0] - '0';
            *ppszText = *ppszText + 1;
        }
        if (nVal > 255 || pszTextBefore == *ppszText) {
            return 0;
        }
        pbyAddrCursor[0] = (unsigned char)nVal;
        pbyAddrCursor = pbyAddrCursor + 1;
        
        if ((*ppszText)[0] == ':' && pnPort != 0) {
            *ppszText = *ppszText + 1;
            pszTextBefore = *ppszText;
            nVal = 0;
            while ((*ppszText)[0] >= '0' && (*ppszText)[0] <= '9') {
                nVal = nVal * 10;
                nVal = nVal + (*ppszText)[0] - '0';
                *ppszText = *ppszText + 1;
            }
            if (nVal > 65535 || pszTextBefore == *ppszText) {
                return 0;
            }
            usPortNetwork = (nVal & 65280) >> 8;
            usPortNetwork = usPortNetwork | (nVal & 255);
            *pnPort = usPortNetwork;
            return 1;
        } else {
            if (pnPort != 0) {
                *pnPort = 0;
            }
            return 1;
        }
    } else {
        pbyZerosLoc = 0;
        bIPv4Detected = 0;
        for (nIdx = 0; nIdx < 8; nIdx = nIdx + 1) {
            pszTextBefore = *ppszText;
            nVal = 0;
            while ((((*ppszText)[0] & 95) >= ('0' & 95) && ((*ppszText)[0] & 95) <= ('9' & 95)) || 
                   ((*ppszText)[0] >= 'A' && (*ppszText)[0] <= 'F')) {
                unsigned char nybbleValue;
                nybbleValue = (*ppszText)[0] - 16;
                nybbleValue = (nybbleValue > 9 ? nybbleValue - 39 : nybbleValue);
                nVal = nVal << 4;
                nVal = nVal + nybbleValue;
                *ppszText = *ppszText + 1;
            }
            if (pszTextBefore == *ppszText) {
                if (pbyZerosLoc != 0) {
                    if (pbyZerosLoc == pbyAddrCursor) {
                        nIdx = nIdx - 1;
                        break;
                    }
                    return 0;
                }
                if ((*ppszText)[0] != ':') {
                    return 0;
                }
                if (nIdx == 0) {
                    *ppszText = *ppszText + 1;
                    if ((*ppszText)[0] != ':') {
                        return 0;
                    }
                }
                pbyZerosLoc = pbyAddrCursor;
                *ppszText = *ppszText + 1;
            } else {
                if ((*ppszText)[0] == '.') {
                    const char* pszTextlocal = pszTextBefore;
                    unsigned char abyAddrlocal[16];
                    int bIsIPv6local;
                    int bParseResultlocal = ParseIPv4OrIPv6(&pszTextlocal, abyAddrlocal, 0, &bIsIPv6local);
                    *ppszText = pszTextlocal;
                    if (bParseResultlocal == 0 || bIsIPv6local != 0) {
                        return 0;
                    }
                    pbyAddrCursor[0] = abyAddrlocal[0];
                    pbyAddrCursor[1] = abyAddrlocal[1];
                    pbyAddrCursor[2] = abyAddrlocal[2];
                    pbyAddrCursor[3] = abyAddrlocal[3];
                    pbyAddrCursor = pbyAddrCursor + 4;
                    nIdx = nIdx + 1;
                    bIPv4Detected = 1;
                    break;
                }
                if (nVal > 65535) {
                    return 0;
                }
                pbyAddrCursor[0] = nVal >> 8;
                pbyAddrCursor[1] = nVal & 255;
                pbyAddrCursor = pbyAddrCursor + 2;
                if ((*ppszText)[0] == ':') {
                    *ppszText = *ppszText + 1;
                } else {
                    break;
                }
            }
        }
        if (pbyZerosLoc != 0) {
            nHead = (int)(pbyZerosLoc - abyAddrLocal);
            nTail = nIdx * 2 - (int)(pbyZerosLoc - abyAddrLocal);
            nZeros = 16 - nTail - nHead;
            for (i = 0; i < nTail; i = i + 1) {
                abyAddrLocal[16 - nTail + i] = pbyZerosLoc[i];
            }
            for (i = 0; i < nZeros; i = i + 1) {
                pbyZerosLoc[i] = 0;
            }
        }
        if (bIPv4Detected != 0) {
            unsigned char abyPfx[12] = {0,0,0,0,0,0,0,0,0,0,255,255};
            for (i = 0; i < 12; i = i + 1) {
                if (abyAddrLocal[i] != abyPfx[i]) {
                    return 0;
                }
            }
        }
        if ((*ppszText)[0] == ']') {
            *ppszText = *ppszText + 1;
        }
        if ((*ppszText)[0] == ':' && pnPort != 0) {
            *ppszText = *ppszText + 1;
            pszTextBefore = *ppszText;
            nVal = 0;
            while ((*ppszText)[0] >= '0' && (*ppszText)[0] <= '9') {
                nVal = nVal * 10;
                nVal = nVal + (*ppszText)[0] - '0';
                *ppszText = *ppszText + 1;
            }
            if (nVal > 65535 || pszTextBefore == *ppszText) {
                return 0;
            }
            usPortNetwork = (nVal & 65280) >> 8;
            usPortNetwork = usPortNetwork | (nVal & 255);
            *pnPort = usPortNetwork;
            return 1;
        } else {
            if (pnPort != 0) {
                *pnPort = 0;
            }
            return 1;
        }
    }
    return;
}
