int func(int input_guess, int* output_result) {
    int number = 42;
    int guess = input_guess;
    int result = 0;
    
    if (number == guess) {
        result = 1;
    } else {
        if (number < guess) {
            result = 2;
        } else {
            result = 3;
        }
    }
    
    *output_result = result;
    return;
}
