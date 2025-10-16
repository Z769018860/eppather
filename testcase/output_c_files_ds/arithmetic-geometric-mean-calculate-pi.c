void agm(int in1[2], int in2[2], int out1[2], int out2[2]) {
    int temp1[2];
    int temp2[2];
    
    temp1[0] = in1[0] + in2[0];
    temp1[1] = in1[1] + in2[1];
    
    out1[0] = temp1[0] / 2;
    out1[1] = temp1[1] / 2;
    
    temp2[0] = in1[0] * in2[0];
    temp2[1] = in1[1] * in2[1];
    
    int sqrt_temp = 1;
    for (int i = 0; i < 10; i = i + 1) {
        sqrt_temp = (sqrt_temp + (temp2[0] / sqrt_temp)) / 2;
    }
    out2[0] = sqrt_temp;
    
    sqrt_temp = 1;
    for (int i = 0; i < 10; i = i + 1) {
        sqrt_temp = (sqrt_temp + (temp2[1] / sqrt_temp)) / 2;
    }
    out2[1] = sqrt_temp;
    
    return;
}
