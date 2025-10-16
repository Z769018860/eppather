int factorial(int num) {
    int result;
    result = 1;
    if (num == 0) {
        result = 1;
    }
    else {
        if (num == 1) {
            result = 1;
        }
        else {
            int temp;
            temp = num - 1;
            temp = factorial(temp);
            result = num * temp;
        }
    }
    return result;
}

int wrapper_function(int input) {
    int response_x;
    int result;
    response_x = input;
    result = factorial(response_x);
    return result;
    return;
}
