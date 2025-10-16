int simulate(int field[2][640*480], int swapu, int prob_f, int prob_p, int prob_tree) {
    int i;
    int j;
    int new_swapu;
    int neighbor_burning;
    
    for (i = 0; i < 640; i = i + 1) {
        for (j = 0; j < 480; j = j + 1) {
            int s = field[swapu][j * 640 + i];
            if (s == 2) {
                field[swapu ^ 1][j * 640 + i] = 0;
            } else if (s == 0) {
                field[swapu ^ 1][j * 640 + i] = (rand() > prob_p) ? 0 : 1;
            } else if (s == 1) {
                neighbor_burning = 0;
                if (i > 0 && j > 0 && field[swapu][(j - 1) * 640 + (i - 1)] == 2) neighbor_burning = 1;
                if (i > 0 && field[swapu][j * 640 + (i - 1)] == 2) neighbor_burning = 1;
                if (i > 0 && j < 479 && field[swapu][(j + 1) * 640 + (i - 1)] == 2) neighbor_burning = 1;
                if (j > 0 && field[swapu][(j - 1) * 640 + i] == 2) neighbor_burning = 1;
                if (j < 479 && field[swapu][(j + 1) * 640 + i] == 2) neighbor_burning = 1;
                if (i < 639 && j > 0 && field[swapu][(j - 1) * 640 + (i + 1)] == 2) neighbor_burning = 1;
                if (i < 639 && field[swapu][j * 640 + (i + 1)] == 2) neighbor_burning = 1;
                if (i < 639 && j < 479 && field[swapu][(j + 1) * 640 + (i + 1)] == 2) neighbor_burning = 1;
                
                if (neighbor_burning) {
                    field[swapu ^ 1][j * 640 + i] = 2;
                } else {
                    field[swapu ^ 1][j * 640 + i] = (rand() > prob_f) ? 1 : 2;
                }
            }
        }
    }
    new_swapu = swapu ^ 1;
    return new_swapu;
}
