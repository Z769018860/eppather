int func() {
    int str[5];
    int array[5];
    int fp[5];
    
    str[0] = 0;
    fp[0] = 0;
    array[0] = 0;
    
    if (str[0] == 0) {
        return;
    }
    
    if (fp[0] == 0) {
        return;
    }
    
    if (array[0] == 0) {
        if (fp[0] == 0) {
            return;
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        array[i] = 0;
    }
    
    return;
}
