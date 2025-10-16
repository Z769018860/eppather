int sha1_hash(int n) {
    int i;
    int result[20];
    int string[12] = {'R','o','s','e','t','t','a',' ','C','o','d','e'};
    int temp;
    
    for (i = 0; i < 20; i = i + 1) {
        result[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp = string[i];
        result[i] = temp;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp = result[i];
        result[i] = temp + 1;
    }
    
    return;
}
