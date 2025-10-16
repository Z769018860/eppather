void generateFirstRank(int rank[9], int pos[8]) {
    int kPos;
    int qPos;
    int bPos1;
    int bPos2;
    int rPos1;
    int rPos2;
    int nPos1;
    int nPos2;
    int i;
    int temp;
    
    for (i = 0; i < 8; i = i + 1) {
        rank[i] = 'e';
        pos[i] = i;
    }
    
    do {
        kPos = 0;
        rPos1 = 0;
        rPos2 = 0;
    } while ((rPos1 - kPos <= 0 && rPos2 - kPos <= 0) || (rPos1 - kPos >= 0 && rPos2 - kPos >= 0) || (rPos1 == rPos2 || kPos == rPos1 || kPos == rPos2));
    
    rank[pos[rPos1]] = 'R';
    rank[pos[kPos]] = 'K';
    rank[pos[rPos2]] = 'R';
    
    temp = pos[rPos1];
    pos[rPos1] = pos[7];
    pos[7] = temp;
    temp = pos[rPos2];
    pos[rPos2] = pos[6];
    pos[6] = temp;
    temp = pos[kPos];
    pos[kPos] = pos[5];
    pos[5] = temp;
    
    do {
        bPos1 = 0;
        bPos2 = 0;
    } while (((pos[bPos1] - pos[bPos2]) % 2 == 0) || (bPos1 == bPos2));
    
    rank[pos[bPos1]] = 'B';
    rank[pos[bPos2]] = 'B';
    
    temp = pos[bPos1];
    pos[bPos1] = pos[4];
    pos[4] = temp;
    temp = pos[bPos2];
    pos[bPos2] = pos[3];
    pos[3] = temp;
    
    do {
        qPos = 0;
        nPos1 = 0;
    } while (qPos == nPos1);
    
    rank[pos[qPos]] = 'Q';
    rank[pos[nPos1]] = 'N';
    
    for (i = 0; i < 8; i = i + 1) {
        if (rank[i] == 'e') {
            rank[i] = 'N';
            break;
        }
    }
    return;
}
