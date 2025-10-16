int vigenere(int argc, char* argv[], int optind, int encrypt, int sign) {
    int NUMLETTERS = 26;
    int BUFSIZE = 4096;
    int keylen = 5;
    int plainlen = 5;
    int shifts[5];
    char key[5];
    char plaintext[5];
    char ciphertext[5];
    int i;
    int j;
    int charcase;
    
    for (i = 0; i < keylen; i = i + 1) {
        if (!((key[i] >= 'A' && key[i] <= 'Z') || (key[i] >= 'a' && key[i] <= 'z'))) {
            return 2;
        }
        if (key[i] >= 'A' && key[i] <= 'Z') {
            charcase = 'A';
        } else {
            charcase = 'a';
        }
        shifts[i] = (key[i] - charcase) * sign;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        plaintext[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        ciphertext[i] = 0;
    }
    
    for (i = 0, j = 0; i < plainlen; i = i + 1) {
        if (!((plaintext[i] >= 'A' && plaintext[i] <= 'Z') || (plaintext[i] >= 'a' && plaintext[i] <= 'z'))) {
            ciphertext[i] = plaintext[i];
            continue;
        }
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            charcase = 'A';
        } else {
            charcase = 'a';
        }
        ciphertext[i] = ((plaintext[i] + shifts[j] - charcase + NUMLETTERS) % NUMLETTERS) + charcase;
        j = (j + 1) % keylen;
    }
    
    return 0;
}
