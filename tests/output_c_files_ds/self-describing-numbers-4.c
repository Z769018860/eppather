void selfdesc() {
    int digits[36] = {0};
    int count[36] = {0};
    int n = 36;
    int i;
    int j;
    
    for (i = 0; i < n; i = i + 1) {
        digits[i] = i;
    }
    
    for (i = 0; i < n; i = i + 1) {
        if (i == 0) {
            count[1] = count[1] + 1;
            count[2] = count[2] + 1;
        } else {
            if (i == 1) {
                count[0] = count[0] + 1;
                count[2] = count[2] + 1;
            } else {
                count[0] = count[0] + 1;
                count[1] = count[1] + 1;
                for (j = 2; j <= i; j = j + 1) {
                    count[j] = count[j] + 1;
                }
            }
        }
    }
    
    return;
}
