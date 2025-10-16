int customMalloc(int size) {
    int mapped[1];
    int entry[3];
    int root[3];
    int tail[3];
    
    if (size == 0) {
        return 0;
    }
    
    mapped[0] = 1;
    
    entry[0] = mapped[0];
    entry[1] = size;
    entry[2] = 0;
    
    if (tail[0] != 0) {
        tail[2] = entry[0];
        tail[0] = tail[2];
    } else {
        root[0] = entry[0];
        tail[0] = entry[0];
    }
    
    tail[0] = entry[0];
    tail[1] = size;
    tail[2] = 0;
    
    return mapped[0];
}

void customFree(int addr) {
    int curNode[3];
    int nextNode[3];
    int size;
    
    curNode[0] = root[0];
    
    if (curNode[0] == 0) {
        return;
    }
    
    if (curNode[0] == addr) {
        root[0] = curNode[2];
        size = curNode[1];
        
        if (root[0] == 0) {
            tail[0] = 0;
        }
        return;
    }
    
    for (; curNode[2] != 0; ) {
        nextNode[0] = curNode[2];
        
        if (nextNode[0] == addr) {
            size = nextNode[1];
            
            if (curNode[2] == tail[0]) {
                tail[0] = curNode[0];
            }
            curNode[2] = nextNode[2];
            return;
        }
        
        curNode[0] = nextNode[0];
    }
    
    return;
}
