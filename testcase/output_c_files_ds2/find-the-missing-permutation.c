void findMissingPermutation(int perms[23][4], int n1, int n2) {
    int i;
    int j;
    int cnt[4];
    int miss[4];
    int n;
    
    n = 1;
    for (i = 1; i < n1; i = i + 1) {
        n = n * i;
    }
    
    for (i = 0; i < n1; i = i + 1) {
        for (j = 0; j < n1; j = j + 1) {
            cnt[j] = 0;
        }
        
        for (j = 0; j < n2; j = j + 1) {
            cnt[perms[j][i] - 65] = cnt[perms[j][i] - 65] + 1;
        }
        
        for (j = 0; j < n1; j = j + 1) {
            if (cnt[j] == n) {
                continue;
            } else {
                break;
            }
        }
        
        miss[i] = j + 65;
    }
    
    return;
}
