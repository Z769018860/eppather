void func() {
    int t_a = 1;
    int t_b = 2;
    int t_c = 3;
    int h_a = 4;
    int h_b = 5;
    int h_c = 6;
    int temp_a;
    int temp_b;
    int temp_c;
    
    temp_a = t_a;
    temp_b = t_b;
    temp_c = t_c;
    t_a = h_a;
    t_b = h_b;
    t_c = h_c;
    h_a = temp_a;
    h_b = temp_b;
    h_c = temp_c;
    
    int pt_a = t_a;
    int th_a = h_a;
    int temp_ptr;
    
    temp_ptr = pt_a;
    pt_a = th_a;
    th_a = temp_ptr;
    
    return;
}
