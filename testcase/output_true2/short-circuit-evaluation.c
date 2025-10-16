int a(int in[5]) {
    return in[0];
}

int b(int in[5]) {
    return in[0];
}

void test(int x[5]) {
    int in1[5];
    int in2[5];
    int in3[5];
    int in4[5];
    
    in1[0] = 0;
    in2[0] = 1;
    in3[0] = 1;
    in4[0] = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        x[0] = a(in1) && b(in2);
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        x[0] = a(in3) || b(in4);
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        x[0] = a(in3) && b(in4);
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        x[0] = a(in1) || b(in1);
    }
    
    return;
}
