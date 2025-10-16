int imprecise_operations(int a_value, int a_delta, int b_value, int b_delta, int c) {
    int ret_value[5];
    int ret_delta[5];
    int temp1[5];
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
    
    temp1[0] = a_value + b_value;
    temp2[0] = a_delta * a_delta;
    temp3[0] = b_delta * b_delta;
    temp4[0] = temp2[0] + temp3[0];
    temp5[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (temp4[0] > 0) {
            temp6[0] = temp4[0];
            temp7[0] = temp6[0] / 2;
            temp8[0] = temp6[0] / temp7[0];
            temp9[0] = temp7[0] + temp8[0];
            temp10[0] = temp9[0] / 2;
            temp4[0] = temp10[0];
            temp5[0] = temp5[0] + 1;
        }
    }
    ret_value[0] = temp1[0];
    ret_delta[0] = temp4[0];
    
    temp11[0] = a_value * b_value;
    temp12[0] = a_value * b_delta;
    temp13[0] = b_value * a_delta;
    temp14[0] = temp12[0] * temp12[0];
    temp15[0] = temp13[0] * temp13[0];
    temp16[0] = temp14[0] + temp15[0];
    temp17[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (temp16[0] > 0) {
            temp18[0] = temp16[0];
            temp19[0] = temp18[0] / 2;
            temp20[0] = temp18[0] / temp19[0];
            temp21[0] = temp19[0] + temp20[0];
            temp22[0] = temp21[0] / 2;
            temp16[0] = temp22[0];
            temp17[0] = temp17[0] + 1;
        }
    }
    ret_value[0] = temp11[0];
    ret_delta[0] = temp16[0];
    
    temp23[0] = a_value / b_value;
    temp24[0] = a_value * b_delta;
    temp25[0] = b_value * a_delta;
    temp26[0] = temp24[0] * temp24[0];
    temp27[0] = temp25[0] * temp25[0];
    temp28[0] = temp26[0] + temp27[0];
    temp29[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (temp28[0] > 0) {
            temp30[0] = temp28[0];
            temp31[0] = temp30[0] / 2;
            temp32[0] = temp30[0] / temp31[0];
            temp33[0] = temp31[0] + temp32[0];
            temp34[0] = temp33[0] / 2;
            temp28[0] = temp34[0];
            temp29[0] = temp29[0] + 1;
        }
    }
    temp35[0] = b_value * b_value;
    temp36[0] = temp28[0] / temp35[0];
    ret_value[0] = temp23[0];
    ret_delta[0] = temp36[0];
    
    temp37[0] = 1;
    for (int i = 0; i < c; i = i + 1) {
        temp37[0] = temp37[0] * a_value;
    }
    temp38[0] = temp37[0] * c;
    temp39[0] = temp38[0] * a_delta;
    temp40[0] = temp39[0] / a_value;
    if (temp40[0] < 0) {
        temp40[0] = -temp40[0];
    }
    ret_value[0] = temp37[0];
    ret_delta[0] = temp40[0];
    
    return;
}
