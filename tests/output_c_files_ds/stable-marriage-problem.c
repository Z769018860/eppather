void stable_marriage() {
    int pairs[21];
    int proposed[21];
    int pref[21][11] = {
        {10,14,12,18,19,13,15,11,17,16},
        {12,17,10,13,14,15,11,19,18,16},
        {17,14,10,13,11,15,18,16,12,19},
        {18,15,13,16,17,14,19,11,12,10},
        {19,13,11,12,15,14,10,18,17,16},
        {11,10,13,16,14,18,12,19,17,15},
        {16,14,18,11,12,10,13,17,19,15},
        {10,14,17,15,18,12,19,11,16,13},
        {17,12,13,16,11,10,15,18,19,14},
        {10,15,19,16,14,11,13,12,18,17},
        {1,5,9,6,7,0,3,4,2,8},
        {1,0,2,5,6,3,7,4,9,8},
        {5,1,4,6,8,2,7,0,3,9},
        {5,9,2,0,7,8,6,3,1,4},
        {9,8,5,3,0,6,2,4,7,1},
        {1,0,4,7,9,3,5,6,2,8},
        {9,6,8,5,1,0,2,4,3,7},
        {6,9,1,0,7,3,8,4,2,5},
        {7,2,8,6,5,1,0,4,9,3},
        {4,8,6,0,1,9,2,7,5,3}
    };
    int i;
    int j;
    int unengaged;
    int man;
    int woman;
    int fiance;
    int rank_this_that;
    int rank_woman_man;
    int rank_woman_fiance;
    int man1;
    int wife2;
    int rank_man1_wife2;
    int rank_man1_pairs_man1;
    int rank_wife2_man1;
    int rank_wife2_pairs_wife2;
    int man2;
    int bad;
    
    for (i = 0; i <= 20; i = i + 1) {
        pairs[i] = -1;
        proposed[i] = -1;
    }
    
    do {
        unengaged = 0;
        for (i = 0; i <= 9; i = i + 1) {
            if (pairs[i] != -1) {
                continue;
            }
            unengaged = 1;
            proposed[i] = proposed[i] + 1;
            woman = pref[i][proposed[i]];
            fiance = pairs[woman];
            
            if (fiance == -1) {
                pairs[i] = woman;
                pairs[woman] = i;
            } else {
                rank_woman_man = 0;
                for (j = 0; j <= 9 && pref[woman][j] != i; j = j + 1) {
                    rank_woman_man = rank_woman_man + 1;
                }
                rank_woman_fiance = 0;
                for (j = 0; j <= 9 && pref[woman][j] != fiance; j = j + 1) {
                    rank_woman_fiance = rank_woman_fiance + 1;
                }
                if (rank_woman_man < rank_woman_fiance) {
                    pairs[fiance] = -1;
                    pairs[woman] = -1;
                    pairs[i] = woman;
                    pairs[woman] = i;
                }
            }
        }
    } while (unengaged);
    
    bad = 0;
    for (i = 0; i < 9; i = i + 1) {
        for (j = i + 1; j <= 9; j = j + 1) {
            man1 = i;
            wife2 = pairs[j];
            rank_man1_wife2 = 0;
            for (int k = 0; k <= 9 && pref[man1][k] != wife2; k = k + 1) {
                rank_man1_wife2 = rank_man1_wife2 + 1;
            }
            rank_man1_pairs_man1 = 0;
            for (int k = 0; k <= 9 && pref[man1][k] != pairs[man1]; k = k + 1) {
                rank_man1_pairs_man1 = rank_man1_pairs_man1 + 1;
            }
            rank_wife2_man1 = 0;
            for (int k = 0; k <= 9 && pref[wife2][k] != man1; k = k + 1) {
                rank_wife2_man1 = rank_wife2_man1 + 1;
            }
            rank_wife2_pairs_wife2 = 0;
            for (int k = 0; k <= 9 && pref[wife2][k] != pairs[wife2]; k = k + 1) {
                rank_wife2_pairs_wife2 = rank_wife2_pairs_wife2 + 1;
            }
            if (rank_man1_wife2 < rank_man1_pairs_man1 && rank_wife2_man1 < rank_wife2_pairs_wife2) {
                bad = 1;
            }
            
            man1 = j;
            wife2 = pairs[i];
            rank_man1_wife2 = 0;
            for (int k = 0; k <= 9 && pref[man1][k] != wife2; k = k + 1) {
                rank_man1_wife2 = rank_man1_wife2 + 1;
            }
            rank_man1_pairs_man1 = 0;
            for (int k = 0; k <= 9 && pref[man1][k] != pairs[man1]; k = k + 1) {
                rank_man1_pairs_man1 = rank_man1_pairs_man1 + 1;
            }
            rank_wife2_man1 = 0;
            for (int k = 0; k <= 9 && pref[wife2][k] != man1; k = k + 1) {
                rank_wife2_man1 = rank_wife2_man1 + 1;
            }
            rank_wife2_pairs_wife2 = 0;
            for (int k = 0; k <= 9 && pref[wife2][k] != pairs[wife2]; k = k + 1) {
                rank_wife2_pairs_wife2 = rank_wife2_pairs_wife2 + 1;
            }
            if (rank_man1_wife2 < rank_man1_pairs_man1 && rank_wife2_man1 < rank_wife2_pairs_wife2) {
                bad = 1;
            }
        }
    }
    
    return;
}
