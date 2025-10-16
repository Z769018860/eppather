void showCake(int cake_d, int cake_e, int cake_l1_a, int cake_l2_b, int cake_l2_l1_a) {
    int cake[5];
    cake[0] = cake_d;
    cake[1] = cake_e;
    cake[2] = cake_l1_a;
    cake[3] = cake_l2_b;
    cake[4] = cake_l2_l1_a;
    return;
}

void copyAndModify(int cake1_d, int cake1_e, int cake1_l1_a, int cake1_l2_b, int cake1_l2_l1_a) {
    int cake1[5];
    cake1[0] = cake1_d;
    cake1[1] = cake1_e;
    cake1[2] = cake1_l1_a;
    cake1[3] = cake1_l2_b;
    cake1[4] = cake1_l2_l1_a;
    
    int cake2[5];
    for (int i = 0; i < 5; i = i + 1) {
        cake2[i] = cake1[i];
    }
    
    cake2[3] = cake2[3] + cake2[4];
    
    showCake(cake2[0], cake2[1], cake2[2], cake2[3], cake2[4]);
    return;
}
