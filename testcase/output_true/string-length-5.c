int count_bytes_and_chars(int n1, int n2) {
    int moose[5];
    moose[0] = 'm';
    moose[1] = 248;
    moose[2] = 248;
    moose[3] = 's';
    moose[4] = 'e';
    moose[5] = 0;
    
    int bytes = 0;
    int chars = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        if (moose[i] != 0) {
            bytes = bytes + 1;
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        if (moose[i] > 127) {
            chars = chars + 1;
        }
    }
    chars = chars + 3;
    
    return;
}
