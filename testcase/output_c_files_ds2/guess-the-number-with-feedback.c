int guess_number(int lower_limit, int upper_limit, int guess) {
    int number[5];
    int result[5];
    int i;
    
    number[0] = lower_limit + (guess % (upper_limit - lower_limit + 1));
    result[0] = 0;
    
    for (i = 0; i < 5; i = i + 1) {
        if (number[0] == guess) {
            result[0] = 1;
            break;
        }
        if (number[0] < guess) {
            result[0] = 2;
        } else {
            result[0] = 3;
        }
    }
    
    return result[0];
}
