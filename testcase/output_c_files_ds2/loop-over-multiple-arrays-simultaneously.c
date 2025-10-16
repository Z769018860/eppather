int func(int n) {
    char a1[5] = {'a','b','c','\0','\0'};
    char a2[5] = {'A','B','C','\0','\0'};
    int a3[5] = {1,2,3,0,0};
    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (i < n) {
            char c1 = a1[i];
            char c2 = a2[i];
            int num = a3[i];
        }
    }
    return;
}
