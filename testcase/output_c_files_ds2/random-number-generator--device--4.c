int generate_random_number(int param1, int param2) {
    int p[5];
    int i[5];
    int result[5];
    result[0] = 0;
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (param1 == param2) {
            result[0] = 1;
        }
    }
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (result[0] == 1) {
            result[0] = 0;
        }
    }
    
    return;
}
