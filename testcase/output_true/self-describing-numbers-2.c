int validate_self_describing_number(int num) {
    int digits[10] = {0};
    int temp = num;
    int i;
    int j;
    
    for (i = 0; i < 10; i = i + 1) {
        digits[i] = 0;
    }
    
    while (temp > 0) {
        int digit = temp % 10;
        digits[digit] = digits[digit] + 1;
        temp = temp / 10;
    }
    
    temp = num;
    for (i = 0; i < 10; i = i + 1) {
        int count = 0;
        int current_digit = temp % 10;
        temp = temp / 10;
        
        for (j = 0; j < 10; j = j + 1) {
            if (digits[j] == i) {
                count = count + 1;
            }
        }
        
        if (count != current_digit) {
            return 0;
        }
    }
    
    return 1;
}
