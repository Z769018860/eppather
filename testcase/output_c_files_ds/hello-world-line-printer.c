void print_hello_world() {
    int i;
    int message[12] = {72, 101, 108, 108, 111, 32, 119, 111, 114, 108, 100, 33};
    int output[12];
    
    for (i = 0; i < 12; i = i + 1) {
        output[i] = message[i];
    }
    
    return;
}
