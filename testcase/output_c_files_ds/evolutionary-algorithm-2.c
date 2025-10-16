void evolveString(int current[28], int target[28]) {
    int temp[28];
    int score;
    int bestScore;
    int i;
    int j;
    int c;
    
    for (i = 0; i < 28; i = i + 1) {
        temp[i] = current[i];
    }
    
    bestScore = 0;
    for (i = 0; i < 28; i = i + 1) {
        if (current[i] == target[i]) {
            bestScore = bestScore + 1;
        }
    }
    
    for (i = 0; i < 28; i = i + 1) {
        for (c = 65; c <= 90; c = c + 1) {
            if (c == 32) {
                continue;
            }
            temp[i] = c;
            score = 0;
            for (j = 0; j < 28; j = j + 1) {
                if (temp[j] == target[j]) {
                    score = score + 1;
                }
            }
            if (score > bestScore) {
                bestScore = score;
                current[i] = c;
            }
            temp[i] = current[i];
        }
    }
    
    for (i = 0; i < 28; i = i + 1) {
        if (current[i] != target[i]) {
            return;
        }
    }
    return;
}
