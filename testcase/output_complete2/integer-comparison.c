void compare(int a, int b) {
    int result[5];
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    
    if (a < b) {
        result[0] = 1;
    }
    
    if (a == b) {
        result[1] = 1;
    }
    
    if (a > b) {
        result[2] = 1;
    }
    
    return;
}
