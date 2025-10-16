int joins(const char *left, const char *right) {
    int len;
    len = 0;
    for (; left[len] != 0; len = len + 1) {
    }
    if (len == 0) {
        return 0;
    }
    if (right[0] == 0) {
        return 0;
    }
    return left[len - 1] == right[0];
}

void amb_problem() {
    const char *w1;
    const char *w2;
    const char *w3;
    const char *w4;
    const char *w1_choices[3] = {"the", "that", "a"};
    const char *w2_choices[3] = {"frog", "elephant", "thing"};
    const char *w3_choices[3] = {"walked", "treaded", "grows"};
    const char *w4_choices[2] = {"slowly", "quickly"};
    int i;
    int j;
    int k;
    int l;

    for (i = 0; i < 3; i = i + 1) {
        w1 = w1_choices[i];
        for (j = 0; j < 3; j = j + 1) {
            w2 = w2_choices[j];
            if (joins(w1, w2) == 0) {
                continue;
            }
            for (k = 0; k < 3; k = k + 1) {
                w3 = w3_choices[k];
                if (joins(w2, w3) == 0) {
                    continue;
                }
                for (l = 0; l < 2; l = l + 1) {
                    w4 = w4_choices[l];
                    if (joins(w3, w4) == 0) {
                        continue;
                    }
                    return;
                }
            }
        }
    }
    return;
}
