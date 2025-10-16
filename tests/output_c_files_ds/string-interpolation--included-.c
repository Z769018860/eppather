void func() {
    char extra[7] = {'l', 'i', 't', 't', 'l', 'e', '\0'};
    char output[20] = {'M', 'a', 'r', 'y', ' ', 'h', 'a', 'd', ' ', 'a', ' ', '\0'};
    int i;
    int j;
    
    for (i = 0; i < 6; i = i + 1) {
        output[11 + i] = extra[i];
    }
    output[17] = ' ';
    output[18] = 'l';
    output[19] = '\0';
    return;
}
