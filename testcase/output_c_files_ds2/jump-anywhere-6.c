void func() {
    int str[5];
    int array[5];
    int fp[5];
    
    for (int i = 0; i < 5; i = i + 1) {
        str[i] = 0;
        array[i] = 0;
        fp[i] = 0;
    }
    
    if (str[0] == 0) {
        goto exit;
    }
    
    if (fp[0] == 0) {
        goto clean_up_str;
    }
    
    if (array[0] == 0) {
        goto clean_up_file;
    }
    
clean_up_array:
    for (int i = 0; i < 5; i = i + 1) {
        array[i] = 0;
    }
clean_up_file:
    for (int i = 0; i < 5; i = i + 1) {
        fp[i] = 0;
    }
clean_up_str:
    for (int i = 0; i < 5; i = i + 1) {
        str[i] = 0;
    }
exit:
    return;
}
