int func() {
    int i;
    const char *s[4];
    s[0] = "%d\n";
    s[1] = "Fizz\n";
    s[2] = s[3] + 4;
    s[3] = "FizzBuzz\n";
    
    for (i = 1; i <= 100; i = i + 1) {
        int mod3;
        int mod5;
        int index;
        
        mod3 = i % 3;
        mod5 = i % 5;
        
        if (mod3 == 0) {
            mod3 = 1;
        } else {
            mod3 = 0;
        }
        
        if (mod5 == 0) {
            mod5 = 1;
        } else {
            mod5 = 0;
        }
        
        index = mod3 + 2 * mod5;
    }
    
    return;
}
