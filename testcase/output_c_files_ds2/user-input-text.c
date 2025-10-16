int func(int buf_size) {
    int str[5];
    int num[5];
    int buf[5];
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        str[i] = 0;
        buf[i] = 0;
    }
    
    num[0] = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (num[0] != 75000) {
            num[0] = 75000;
        }
    }
    
    return;
}
