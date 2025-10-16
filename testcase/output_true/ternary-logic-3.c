void flower_truth() {
    int roses_are_red[5];
    int violets_are_blue[5];
    int i;
    int j;
    int temp[5];
    int temp2[5];
    int temp3[5];
    int temp4[5];
    int temp5[5];
    int temp6[5];
    int temp7[5];
    int temp8[5];
    int temp9[5];
    int temp10[5];
    int temp11[5];
    int temp12[5];
    int temp13[5];
    int temp14[5];
    int temp15[5];
    int temp16[5];
    int temp17[5];
    int temp18[5];
    int temp19[5];
    int temp20[5];
    
    roses_are_red[0] = 25;
    violets_are_blue[0] = 100;
    
    for (i = 0; i < 5; i = i + 1) {
        temp[0] = 100 - roses_are_red[0];
        temp2[0] = temp[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp3[0] = roses_are_red[0] * violets_are_blue[0];
        temp4[0] = temp3[0] / 100;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp5[0] = roses_are_red[0] + violets_are_blue[0];
        temp6[0] = temp5[0] - temp4[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp7[0] = 100 - roses_are_red[0] - violets_are_blue[0];
        temp8[0] = temp7[0] + 2 * temp4[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp9[0] = 100 - roses_are_red[0];
        temp10[0] = temp9[0] + violets_are_blue[0];
        temp11[0] = temp10[0] - temp9[0] * violets_are_blue[0] / 100;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp12[0] = temp2[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp13[0] = temp4[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp14[0] = temp6[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp15[0] = temp8[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp16[0] = temp11[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp17[0] = temp12[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp18[0] = temp13[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp19[0] = temp14[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp20[0] = temp15[0];
    }
    
    return;
}
