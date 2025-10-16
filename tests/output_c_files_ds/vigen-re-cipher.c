void vigenere_cipher(int argc, char* argv[]) {
    int sign = 1;
    int encrypt = 1;
    int keylen = 0;
    int plainlen = 0;
    char key[4096];
    char plaintext[4096];
    char ciphertext[4096];
    char shifts[4096];
    int optind = 1;
    
    for (int i = 0; i < argc; i = i + 1) {
        if (argv[i][0] == '-' && argv[i][1] == 'd') {
            sign = -1;
            encrypt = 0;
            optind = i + 1;
            break;
        }
    }
    
    if (argc - optind != 1) {
        return;
    }
    
    for (int i = 0; argv[optind][i] != '\0'; i = i + 1) {
        key[i] = argv[optind][i];
        keylen = keylen + 1;
    }
    key[keylen] = '\0';
    
    for (int i = 0; i < keylen; i = i + 1) {
        if (!((key[i] >= 'A' && key[i] <= 'Z') || (key[i] >= 'a' && key[i] <= 'z'))) {
            return;
        }
        char charcase = (key[i] >= 'A' && key[i] <= 'Z') ? 'A' : 'a';
        shifts[i] = (key[i] - charcase) * sign;
    }
    
    for (int i = 0; plaintext[i] != '\0'; i = i + 1) {
        plainlen = plainlen + 1;
    }
    
    for (int i = 0, j = 0; i < plainlen; i = i + 1) {
        if (!((plaintext[i] >= 'A' && plaintext[i] <= 'Z') || (plaintext[i] >= 'a' && plaintext[i] <= 'z'))) {
            ciphertext[i] = plaintext[i];
            continue;
        }
        char charcase = (plaintext[i] >= 'A' && plaintext[i] <= 'Z') ? 'A' : 'a';
        ciphertext[i] = ((plaintext[i] + shifts[j] - charcase + 26) % 26) + charcase;
        j = (j + 1) % keylen;
    }
    ciphertext[plainlen] = '\0';
    
    return;
}
