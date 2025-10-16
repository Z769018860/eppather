void safe_add(int interval[2], int a, int b) {
    int orig;
    int n;
    int i;
    int nums[5][2];
    int ival[2];
    
    for (i = 0; i < 5; i = i + 1) {
        nums[i][0] = 0;
        nums[i][1] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        ival[0] = 0;
        ival[1] = 0;
    }
    
    orig = 0;
    n = 0;
    
    interval[0] = a + b;
    interval[1] = a + b;
    
    return;
}
