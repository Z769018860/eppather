void filterLines(int dummy) {
    int lines[7][4] = {{0}};
    int lengths[7] = {1, 2, 3, 3, 2, 1, 3};
    int i;
    int j;
    
    for (i = 0; i < 7; i = i + 1) {
        if (lengths[i] >= 3) {
            for (j = 0; j < lengths[i]; j = j + 1) {
                lines[i][j] = 1;
            }
        }
    }
    
    for (i = 0; i < 7; i = i + 1) {
        if (lengths[i] >= 3) {
            for (j = 0; j < lengths[i]; j = j + 1) {
                if (lines[i][j] == 1) {
                    lines[i][j] = lines[i][j];
                }
            }
        }
    }
    return;
}
