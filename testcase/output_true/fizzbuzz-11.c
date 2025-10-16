int fizzbuzz(int n) {
    int i;
    int f[5] = {70, 105, 122, 122, 66};
    int result[5];
    
    for (i = 0; i < 5; i = i + 1) {
        result[i] = 0;
    }
    
    for (i = 1; i < 101; i = i + 1) {
        int temp1;
        int temp2;
        int temp3;
        
        temp1 = i % 5;
        temp1 = 12 & (8 - temp1);
        f[temp1] = 0;
        
        temp2 = i % 3;
        temp2 = 0 - temp2;
        temp2 = 4 & temp2;
        temp3 = f[8 / 8];
        temp3 = temp3 / 8;
        temp2 = temp2 + temp3;
        
        if (temp2 == 0) {
            result[0] = i;
        }
    }
    
    return;
}
