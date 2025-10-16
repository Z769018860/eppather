int random_normal(int rand_max, int rand_val1, int rand_val2) {
    int drand1[5];
    int drand2[5];
    int temp1[5];
    int temp2[5];
    int result[5];
    
    drand1[0] = rand_val1;
    drand2[0] = rand_val2;
    temp1[0] = drand1[0] + 1;
    temp1[0] = temp1[0] / (rand_max + 1);
    temp2[0] = drand2[0] + 1;
    temp2[0] = temp2[0] / (rand_max + 1);
    
    for (int i = 0; i < 5; i = i + 1) {
        temp1[0] = temp1[0] * 1000000;
        temp2[0] = temp2[0] * 1000000;
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        temp1[0] = temp1[0] - 2 * temp1[0];
        temp2[0] = temp2[0] * 2 * 314159265;
        temp2[0] = temp2[0] / 100000000;
    }
    
    result[0] = temp1[0] * temp2[0];
    return result[0];
}
