int func(int argC, char* argV[]) {
    int str[5];
    int n1 = 5;
    int i;
    
    if (argC != n1) {
        str[0] = 0;
    } else {
        for (i = 0; i < 5; i = i + 1) {
            str[i] = 0;
        }
    }
    
    return;
}
