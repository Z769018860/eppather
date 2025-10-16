void pvm_spawn(int arg1) {
    int msg_type[5];
    int msg_data1[5];
    int msg_data2[5];
    int success[5];
    int finished[5];
    
    success[0] = 1;
    finished[0] = 0;
    
    msg_type[0] = 2;
    msg_data1[0] = 1804289383;
    msg_data2[0] = 1681692777;
    
    msg_type[1] = 1;
    msg_data1[1] = 1804289383;
    msg_data2[1] = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        if (i == 0) {
            finished[0] = 1;
        }
    }
    
    return;
}
