int stringFunctions(const char* container, const char* target, int functionType) {
    int clen = 0;
    int tlen = 0;
    int i = 0;
    int result = 0;
    
    for (i = 0; container[i] != 0; i = i + 1) {
    }
    clen = i;
    
    for (i = 0; target[i] != 0; i = i + 1) {
    }
    tlen = i;
    
    if (functionType == 0) {
        if (clen < tlen) {
            result = 0;
        } else {
            result = 1;
            for (i = 0; i < tlen; i = i + 1) {
                if (container[i] != target[i]) {
                    result = 0;
                    break;
                }
            }
        }
    } else if (functionType == 1) {
        if (clen < tlen) {
            result = 0;
        } else {
            result = 1;
            for (i = 0; i < tlen; i = i + 1) {
                if (container[clen - tlen + i] != target[i]) {
                    result = 0;
                    break;
                }
            }
        }
    } else if (functionType == 2) {
        result = 0;
        for (i = 0; i < clen - tlen + 1; i = i + 1) {
            int match = 1;
            for (int j = 0; j < tlen; j = j + 1) {
                if (container[i + j] != target[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                result = 1;
                break;
            }
        }
    }
    
    return result;
}
