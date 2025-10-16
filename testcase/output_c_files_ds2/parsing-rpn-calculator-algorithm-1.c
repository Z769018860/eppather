void rpn(int s_len, char s[5])
{
    int stack[256];
    int depth;
    depth = 0;
    int a[5];
    int b[5];
    int i[5];
    int e[5];
    int w[5];
    w[0] = 32;
    w[1] = 9;
    w[2] = 10;
    w[3] = 13;
    w[4] = 12;

    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (s[i[0]] == w[0] || s[i[0]] == w[1] || s[i[0]] == w[2] || s[i[0]] == w[3] || s[i[0]] == w[4]) {
            continue;
        }
        a[0] = 0;
        e[0] = i[0];
        while (e[0] < 5 && s[e[0]] >= 48 && s[e[0]] <= 57) {
            a[0] = a[0] * 10 + (s[e[0]] - 48);
            e[0] = e[0] + 1;
        }
        if (e[0] > i[0]) {
            if (depth >= 256) {
                return;
            }
            stack[depth] = a[0];
            depth = depth + 1;
        } else {
            if (s[i[0]] == '+') {
                if (depth < 1) {
                    return;
                }
                b[0] = stack[depth - 1];
                depth = depth - 1;
                if (depth < 1) {
                    return;
                }
                a[0] = stack[depth - 1];
                depth = depth - 1;
                stack[depth] = a[0] + b[0];
                depth = depth + 1;
            } else if (s[i[0]] == '-') {
                if (depth < 1) {
                    return;
                }
                b[0] = stack[depth - 1];
                depth = depth - 1;
                if (depth < 1) {
                    return;
                }
                a[0] = stack[depth - 1];
                depth = depth - 1;
                stack[depth] = a[0] - b[0];
                depth = depth + 1;
            } else if (s[i[0]] == '*') {
                if (depth < 1) {
                    return;
                }
                b[0] = stack[depth - 1];
                depth = depth - 1;
                if (depth < 1) {
                    return;
                }
                a[0] = stack[depth - 1];
                depth = depth - 1;
                stack[depth] = a[0] * b[0];
                depth = depth + 1;
            } else if (s[i[0]] == '/') {
                if (depth < 1) {
                    return;
                }
                b[0] = stack[depth - 1];
                depth = depth - 1;
                if (depth < 1) {
                    return;
                }
                a[0] = stack[depth - 1];
                depth = depth - 1;
                stack[depth] = a[0] / b[0];
                depth = depth + 1;
            } else {
                return;
            }
        }
    }

    if (depth != 1) {
        return;
    }
    return;
}
