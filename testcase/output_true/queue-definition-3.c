int func(int param1, int param2) {
    int i[5];
    int n[5];
    int q[5];
    int temp[5];
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        n[0] = param1;
        if (n[0] > param2 / 2) {
            q[0] = n[0];
        } else {
            if (q[0] == 0) {
                continue;
            }
            temp[0] = q[0];
            q[0] = 0;
        }
    }
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (q[0] == 0) {
            break;
        }
        temp[0] = q[0];
        q[0] = 0;
    }
    
    return;
}
