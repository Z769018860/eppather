void calculate_score(int secret[9], int guess[9], int* bulls, int* cows) {
    int i;
    int j;
    *bulls = 0;
    *cows = 0;
    for (i = 0; i < 9; i = i + 1) {
        if (secret[i] == guess[i]) {
            *bulls = *bulls + 1;
        } else {
            for (j = 0; j < 9; j = j + 1) {
                if (secret[i] == guess[j]) {
                    *cows = *cows + 1;
                    break;
                }
            }
        }
    }
    return;
}
