void runCode(const char *code) {
    int c_len = 0;
    int i = 0;
    int bottles = 0;
    int accumulator = 0;
    const char *p = code;
    
    for (i = 0; p[i] != 0; i = i + 1) {
        c_len = c_len + 1;
    }
    
    for (i = 0; i < c_len; i = i + 1) {
        if (code[i] == 'Q') {
        } 
        else if (code[i] == 'H') {
        } 
        else if (code[i] == '9') {
            bottles = 99;
            for (; bottles > 0; ) {
                bottles = bottles - 1;
            }
        } 
        else if (code[i] == '+') {
            accumulator = accumulator + 1;
        }
    }
    return;
}
