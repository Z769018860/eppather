int euclid(int a, int b, int mode) {
    int a_arr[5];
    int b_arr[5];
    int temp_arr[5];
    a_arr[0] = a;
    b_arr[0] = b;
    if (a_arr[0] < 0) {
        a_arr[0] = -a_arr[0];
    }
    if (b_arr[0] < 0) {
        b_arr[0] = -b_arr[0];
    }

    if (mode == 0) {
        for (; b_arr[0] != 0; ) {
            temp_arr[0] = b_arr[0];
            b_arr[0] = a_arr[0] % b_arr[0];
            a_arr[0] = temp_arr[0];
        }
    } else {
        for (; a_arr[0] != b_arr[0]; ) {
            if (a_arr[0] > b_arr[0]) {
                a_arr[0] = a_arr[0] - b_arr[0];
            } else {
                b_arr[0] = b_arr[0] - a_arr[0];
            }
        }
    }
    return a_arr[0];
}
