int func(int n1) {
    char array[10] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
    int i;
    int result[5];
    
    for (i = 0; i < 5; i = i + 1) {
        result[0] = (i * 1103515245 + 12345) % 10;
        if (result[0] < 0) {
            result[0] = -result[0];
        }
        result[0] = array[result[0]];
    }
    
    return;
}
