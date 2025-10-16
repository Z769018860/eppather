void bulls_and_cows(int secret, int guess, int* bulls, int* cows) {
    int secret_digits[4];
    int guess_digits[4];
    int i;
    int j;
    
    for (i = 0; i < 4; i = i + 1) {
        secret_digits[i] = secret % 10;
        secret = secret / 10;
        guess_digits[i] = guess % 10;
        guess = guess / 10;
    }
    
    bulls[0] = 0;
    cows[0] = 0;
    
    for (i = 0; i < 4; i = i + 1) {
        if (secret_digits[i] == guess_digits[i]) {
            bulls[0] = bulls[0] + 1;
        } else {
            for (j = 0; j < 4; j = j + 1) {
                if (secret_digits[i] == guess_digits[j]) {
                    cows[0] = cows[0] + 1;
                    break;
                }
            }
        }
    }
    
    return;
}
