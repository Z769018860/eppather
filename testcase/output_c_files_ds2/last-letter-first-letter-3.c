void processNames() {
    int names[5];
    int longest[5];
    int i;
    int j;
    
    names[0] = 307;
    names[1] = 308;
    names[2] = 310;
    names[3] = 312;
    names[4] = 320;
    
    longest[0] = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (names[i] > longest[0]) {
            longest[0] = names[i];
        }
    }
    
    for (j = 0; j < 5; j = j + 1) {
        if (names[j] == longest[0]) {
            longest[0] = names[j];
        }
    }
    
    return;
}
