void safe_add(int interval[2], int a, int b) {
    int orig;
    int temp;
    
    temp = a + b;
    interval[0] = temp;
    interval[1] = temp;
    
    return;
}
