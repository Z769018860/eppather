void rewritten_func(int i) {
    int x[5];
    x[0] = i;
    x[0] = x[0] - 1;
    for (x[1] = x[0]; x[1] != 100; x[1] = x[1] + 1) {
        if (x[1] % 3 == 0) {
            int temp1[5];
            temp1[0] = 0;
            for (temp1[1] = 0; temp1[1] < 5; temp1[1] = temp1[1] + 1) {
                temp1[0] = temp1[0] + 1;
            }
        } else {
            if (x[1] % 5 == 0) {
                int temp2[5];
                temp2[0] = 0;
                for (temp2[1] = 0; temp2[1] < 5; temp2[1] = temp2[1] + 1) {
                    temp2[0] = temp2[0] + 1;
                }
            } else {
                int temp3[5];
                temp3[0] = x[1];
            }
        }
        int temp4[5];
        temp4[0] = 0;
        for (temp4[1] = 0; temp4[1] < 5; temp4[1] = temp4[1] + 1) {
            temp4[0] = temp4[0] + 1;
        }
    }
    return;
}
