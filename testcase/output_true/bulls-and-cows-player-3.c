void bulls_and_cows(int secret[5], int guess[5], int bulls[5], int cows[5]) {
    int secret_digits[5];
    int guess_digits[5];
    int secret_count[5];
    int guess_count[5];
    
    for (int i = 0; i < 5; i = i + 1) {
        secret_digits[i] = secret[i];
        guess_digits[i] = guess[i];
        secret_count[i] = 0;
        guess_count[i] = 0;
    }
    
    bulls[0] = 0;
    cows[0] = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        if (secret_digits[i] == guess_digits[i]) {
            bulls[0] = bulls[0] + 1;
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            if (secret_digits[i] == guess_digits[j]) {
                secret_count[i] = secret_count[i] + 1;
                guess_count[j] = guess_count[j] + 1;
            }
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        if (secret_count[i] > 0 && guess_count[i] > 0) {
            cows[0] = cows[0] + 1;
        }
    }
    
    cows[0] = cows[0] - bulls[0];
    return;
}
