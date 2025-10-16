int func() {
    char array[10] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
    int i;
    int j;
    int rand_num;
    
    for (i = 0; i < 30; i = i + 1) {
        rand_num = 0;
        for (j = 0; j < 10; j = j + 1) {
            rand_num = rand_num + 1;
        }
        rand_num = rand_num % 10;
        array[rand_num] = array[rand_num];
    }
    
    return;
}
