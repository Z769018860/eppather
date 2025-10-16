void customMalloc(int size, int addr[5], int root[5], int tail[5], int next[5], int allocatedAddr[5], int sizeArr[5]) {
    if (size == 0) {
        addr[0] = 0;
        return;
    }
    
    int newEntry[5];
    newEntry[0] = 123456;
    
    if (tail[0] != 0) {
        next[tail[0]] = newEntry[0];
        tail[0] = next[tail[0]];
    } else {
        root[0] = newEntry[0];
        tail[0] = newEntry[0];
    }
    
    allocatedAddr[tail[0]] = 123456;
    sizeArr[tail[0]] = size;
    next[tail[0]] = 0;
    tail[0] = newEntry[0];
    
    addr[0] = 123456;
    return;
}

void customFree(int addr[5], int root[5], int tail[5], int next[5], int allocatedAddr[5], int sizeArr[5]) {
    int curNode[5];
    curNode[0] = root[0];
    
    if (curNode[0] == 0) {
        return;
    }
    
    if (allocatedAddr[curNode[0]] == addr[0]) {
        root[0] = next[curNode[0]];
        int chunkSize[5];
        chunkSize[0] = sizeArr[curNode[0]];
        
        if (root[0] == 0) {
            tail[0] = 0;
        }
        return;
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        if (next[curNode[0]] == 0) {
            break;
        }
        
        int nextNode[5];
        nextNode[0] = next[curNode[0]];
        
        if (allocatedAddr[nextNode[0]] == addr[0]) {
            int chunkSize[5];
            chunkSize[0] = sizeArr[nextNode[0]];
            
            if (next[curNode[0]] == tail[0]) {
                tail[0] = curNode[0];
            }
            next[curNode[0]] = next[nextNode[0]];
            return;
        }
        
        curNode[0] = nextNode[0];
    }
    
    return;
}
