void roots_quadratic_eq2(int a, int b, int c, int x[2][2]) {
    int b_div_a[5];
    int c_div_a[5];
    int delta[5];
    int root[5];
    int sol[5];
    int temp[5];
    
    b_div_a[0] = b / a;
    c_div_a[0] = c / a;
    delta[0] = b_div_a[0] * b_div_a[0] - 4 * c_div_a[0];
    
    if (delta[0] < 0) {
        temp[0] = 0 - b_div_a[0];
        temp[0] = temp[0] / 2;
        temp[1] = 0 - delta[0];
        temp[2] = 0;
        for (int i = 0; i < 5; i = i + 1) {
            temp[2] = temp[2] + 1;
            if (temp[2] * temp[2] > temp[1]) {
                temp[2] = temp[2] - 1;
                break;
            }
        }
        x[0][0] = temp[0];
        x[0][1] = temp[2] / 2;
        x[1][0] = temp[0];
        x[1][1] = 0 - temp[2] / 2;
    } else {
        root[0] = 0;
        for (int i = 0; i < 5; i = i + 1) {
            root[0] = root[0] + 1;
            if (root[0] * root[0] > delta[0]) {
                root[0] = root[0] - 1;
                break;
            }
        }
        if (b_div_a[0] > 0) {
            sol[0] = (0 - b_div_a[0] - root[0]) / 2;
        } else {
            sol[0] = (0 - b_div_a[0] + root[0]) / 2;
        }
        x[0][0] = sol[0];
        x[0][1] = 0;
        x[1][0] = c_div_a[0] / sol[0];
        x[1][1] = 0;
    }
    return;
}
