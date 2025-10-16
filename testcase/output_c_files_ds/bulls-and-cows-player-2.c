void calculate_score(int secret, int guess, int* bulls, int* cows) {
    int secret_digits[4];
    int guess_digits[4];
    int secret_temp = secret;
    int guess_temp = guess;
    int i;
    int j;
    
    for (i = 0; i < 4; i = i + 1) {
        secret_digits[3 - i] = secret_temp % 10;
        secret_temp = secret_temp / 10;
        guess_digits[3 - i] = guess_temp % 10;
        guess_temp = guess_temp / 10;
    }
    
    *bulls = 0;
    *cows = 0;
    
    for (i = 0; i < 4; i = i + 1) {
        if (secret_digits[i] == guess_digits[i]) {
            *bulls = *bulls + 1;
        }
    }
    
    for (i = 0; i < 4; i = i + 1) {
        for (j = 0; j < 4; j = j + 1) {
            if (secret_digits[i] == guess_digits[j] && i != j) {
                *cows = *cows + 1;
                break;
            }
        }
    }
    
    return;
}
