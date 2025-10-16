void safe_add(int interval[2], int a, int b) {
    int orig;
    int temp;
    
    orig = 0;
    temp = a + b;
    interval[0] = temp;
    temp = a + b;
    interval[1] = temp;
    
    return;
}
