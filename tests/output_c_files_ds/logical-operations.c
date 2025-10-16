void print_logic(int a, int b) {
    int and_result;
    int or_result;
    int not_result;
    
    and_result = 0;
    if (a != 0 && b != 0) {
        and_result = 1;
    }
    
    or_result = 0;
    if (a != 0 || b != 0) {
        or_result = 1;
    }
    
    not_result = 0;
    if (a == 0) {
        not_result = 1;
    }
    
    return;
}
