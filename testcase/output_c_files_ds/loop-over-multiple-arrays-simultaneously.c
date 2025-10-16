void func() {
    char a1[3];
    char a2[3];
    int a3[3];
    int i;
    
    a1[0] = 'a';
    a1[1] = 'b';
    a1[2] = 'c';
    a2[0] = 'A';
    a2[1] = 'B';
    a2[2] = 'C';
    a3[0] = 1;
    a3[1] = 2;
    a3[2] = 3;
    
    for (i = 0; i < 3; i = i + 1) {
        char c1;
        char c2;
        int n;
        
        c1 = a1[i];
        c2 = a2[i];
        n = a3[i];
    }
    
    return;
}
