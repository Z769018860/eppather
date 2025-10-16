void filter_lines(int max_length) {
    char line[100];
    int length;
    int i;
    int j;
    int c;
    
    for (i = 0; i < 100; i = i + 1) {
        line[i] = 0;
    }
    
    for (i = 0; ; i = i + 1) {
        length = 0;
        for (j = 0; j < 100; j = j + 1) {
            c = getchar();
            if (c == '\n' || c == EOF) {
                break;
            }
            line[j] = c;
            length = length + 1;
        }
        
        if (length >= max_length) {
            for (j = 0; j < length; j = j + 1) {
                putchar(line[j]);
            }
            putchar('\n');
        }
        
        if (c == EOF) {
            break;
        }
    }
    
    return;
}
