int tree_eq(int t1, int t2, int x[5], int y[5], int z[5]) {
    int node_v[5] = {0};
    int node_left[5] = {0};
    int node_right[5] = {0};
    int stack1[5] = {0};
    int stack2[5] = {0};
    int c1_in[5] = {0};
    int c1_out[5] = {0};
    int c2_in[5] = {0};
    int c2_out[5] = {0};
    int p[5] = {0};
    int q[5] = {0};
    int i = 0;
    int j = 0;
    int k = 0;
    int result = 0;

    for (i = 0; i < 5; i = i + 1) {
        node_v[i] = 0;
        node_left[i] = 0;
        node_right[i] = 0;
    }

    c1_in[0] = t1;
    c2_in[0] = t2;

    for (k = 0; k < 5; k = k + 1) {
        stack1[0] = c1_in[0];
        stack2[0] = c2_in[0];
        i = 0;
        while (i < 5) {
            if (stack1[i] != 0) {
                stack1[i + 1] = node_left[stack1[i]];
                stack1[i] = node_right[stack1[i]];
                i = i + 1;
            } else {
                if (i > 0) {
                    i = i - 1;
                    p[0] = stack1[i];
                    c1_out[0] = p[0];
                    break;
                } else {
                    p[0] = 0;
                    break;
                }
            }
        }

        i = 0;
        while (i < 5) {
            if (stack2[i] != 0) {
                stack2[i + 1] = node_left[stack2[i]];
                stack2[i] = node_right[stack2[i]];
                i = i + 1;
            } else {
                if (i > 0) {
                    i = i - 1;
                    q[0] = stack2[i];
                    c2_out[0] = q[0];
                    break;
                } else {
                    q[0] = 0;
                    break;
                }
            }
        }

        if (p[0] == 0 || q[0] == 0 || node_v[p[0]] != node_v[q[0]]) {
            break;
        }
    }

    if (p[0] == 0 && q[0] == 0) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}
