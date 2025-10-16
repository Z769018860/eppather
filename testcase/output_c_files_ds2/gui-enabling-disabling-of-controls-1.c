void combined_function(int min_val, int max_val, int n) {
    int controls[5];
    int increment_enabled[5];
    int decrement_enabled[5];
    
    for (int i = 0; i < 5; i = i + 1) {
        controls[i] = 0;
        increment_enabled[i] = 0;
        decrement_enabled[i] = 0;
    }
    
    if (n < max_val) {
        n = n + 1;
        controls[0] = n;
        for (int i = 0; i < 5; i = i + 1) {
            increment_enabled[i] = (controls[0] < max_val) ? 1 : 0;
            decrement_enabled[i] = (controls[0] > min_val) ? 1 : 0;
        }
    }
    
    if (n > min_val) {
        n = n - 1;
        controls[0] = n;
        for (int i = 0; i < 5; i = i + 1) {
            increment_enabled[i] = (controls[0] < max_val) ? 1 : 0;
            decrement_enabled[i] = (controls[0] > min_val) ? 1 : 0;
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        increment_enabled[i] = (controls[0] < max_val) ? 1 : 0;
        decrement_enabled[i] = (controls[0] > min_val) ? 1 : 0;
    }
    
    return;
}
