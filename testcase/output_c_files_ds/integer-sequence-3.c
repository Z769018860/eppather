void rewritten_function() {
    int i[1];
    int s[1];
    
    i[0] = 0;
    for (;;) {
        i[0] = i[0] + 1;
        s[0] = i[0];
        if (s[0] == 0) {
            return;
        }
    }
    return;
}
