int func(int n1, int n2) {
    int a[5][5];
    int ds[5];
    int n;
    int nn;
    
    n = 0;
    a[n][0] = 'H';
    a[n][1] = 'e';
    a[n][2] = 'l';
    a[n][3] = 'l';
    a[n][4] = 'o';
    n = n + 1;
    
    a[n][0] = 'H';
    a[n][1] = 'o';
    a[n][2] = 'w';
    n = n + 1;
    
    a[n][0] = 'A';
    a[n][1] = 'r';
    a[n][2] = 'e';
    n = n + 1;
    
    a[n][0] = 'Y';
    a[n][1] = 'o';
    a[n][2] = 'u';
    n = n + 1;
    
    a[n][0] = 'T';
    a[n][1] = 'o';
    a[n][2] = 'd';
    a[n][3] = 'a';
    a[n][4] = 'y';
    n = n + 1;
    
    for (nn = 0; nn < 5; nn = nn + 1) {
        for (n2 = 0; n2 < 5; n2 = n2 + 1) {
            if (a[nn][n2] == 0) {
                break;
            }
        }
    }
    
    return;
}
