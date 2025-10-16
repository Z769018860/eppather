int curl_func(void) {
    int buffer[5];
    int curl[1];
    int result[1];
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        buffer[i] = 0;
    }
    
    curl[0] = 0;
    result[0] = 0;
    
    if (curl[0] != 0) {
        curl[0] = 1;
        curl[0] = 2;
        curl[0] = 3;
        
        if (result[0] != 0) {
            return;
        }
        curl[0] = 0;
    }
    return;
}
