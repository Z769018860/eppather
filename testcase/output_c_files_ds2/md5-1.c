int compute_md5(int n) {
    int result[16];
    int string[5];
    string[0] = 'T';
    string[1] = 'h';
    string[2] = 'e';
    string[3] = ' ';
    string[4] = 'q';
    
    int i;
    for (i = 0; i < 16; i = i + 1) {
        result[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        result[i % 16] = result[i % 16] + string[i];
    }
    
    for (i = 0; i < 16; i = i + 1) {
        result[i] = result[i] & 255;
    }
    
    return;
}
