int joins(int left[5], int right[5]) {
    int len_left;
    len_left = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (left[i] == 0) {
            break;
        }
        len_left = len_left + 1;
    }
    int len_right;
    len_right = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (right[i] == 0) {
            break;
        }
        len_right = len_right + 1;
    }
    if (len_left > 0 && len_right > 0) {
        if (left[len_left - 1] == right[0]) {
            return 1;
        }
    }
    return 0;
}

void amb(int argc, int choices[5][5], int result[5]) {
    int w1[5] = {116, 104, 101, 0};
    int w2[5] = {116, 104, 97, 116, 0};
    int w3[5] = {97, 0};
    int w4[5] = {102, 114, 111, 103, 0};
    int w5[5] = {101, 108, 101, 112, 0};
    int w6[5] = {116, 104, 105, 110, 0};
    int w7[5] = {119, 97, 108, 107, 0};
    int w8[5] = {116, 114, 101, 97, 0};
    int w9[5] = {103, 114, 111, 119, 0};
    int w10[5] = {115, 108, 111, 119, 0};
    int w11[5] = {113, 117, 105, 99, 0};

    int words[11][5] = {
        {116, 104, 101, 0},
        {116, 104, 97, 116, 0},
        {97, 0},
        {102, 114, 111, 103, 0},
        {101, 108, 101, 112, 0},
        {116, 104, 105, 110, 0},
        {119, 97, 108, 107, 0},
        {116, 114, 101, 97, 0},
        {103, 114, 111, 119, 0},
        {115, 108, 111, 119, 0},
        {113, 117, 105, 99, 0}
    };

    for (int i1 = 0; i1 < 3; i1 = i1 + 1) {
        for (int i2 = 0; i2 < 3; i2 = i2 + 1) {
            for (int i3 = 0; i3 < 3; i3 = i3 + 1) {
                for (int i4 = 0; i4 < 2; i4 = i4 + 1) {
                    if (joins(words[i1], words[i2 + 3]) && joins(words[i2 + 3], words[i3 + 6]) && joins(words[i3 + 6], words[i4 + 9])) {
                        for (int j = 0; j < 5; j = j + 1) {
                            result[j] = words[i1][j];
                        }
                        return;
                    }
                }
            }
        }
    }
    return;
}
