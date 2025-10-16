void huffman_combined(int freq_size, int pool_size, int q_size, int code_size, int buf_size, int c_size, int s_size) {
    int pool[256][4] = {0};
    int qqq[255];
    int q[255];
    int qend = 1;
    int n_nodes = 0;
    int code[128][16] = {0};
    int buf[1024];
    int c[16];
    int s[16];
    int freq[128] = {0};
    int i;
    int j;
    int l;
    int n[4];
    int t[4];
    int out[1024];
    int len;
    int k;

    for (i = 0; i < freq_size; i = i + 1) {
        if (freq[i] != 0) {
            n[0] = pool[n_nodes][0];
            n[1] = pool[n_nodes][1];
            n[2] = freq[i];
            n[3] = i;
            n_nodes = n_nodes + 1;
            q[qend] = n[0];
            qend = qend + 1;
            j = qend - 1;
            while (j != 1) {
                if (q[j / 2 * 4 + 2] <= n[2]) {
                    break;
                }
                q[j] = q[j / 2];
                j = j / 2;
            }
            q[j] = n[0];
        }
    }

    while (qend > 2) {
        n[0] = q[1];
        if (qend < 2) {
            break;
        }
        qend = qend - 1;
        i = 1;
        while (i * 2 < qend) {
            l = i * 2;
            if (l + 1 < qend && q[l + 1 * 4 + 2] < q[l * 4 + 2]) {
                l = l + 1;
            }
            q[i] = q[l];
            i = l;
        }
        q[i] = q[qend];
        t[0] = q[1];
        if (qend < 2) {
            break;
        }
        qend = qend - 1;
        i = 1;
        while (i * 2 < qend) {
            l = i * 2;
            if (l + 1 < qend && q[l + 1 * 4 + 2] < q[l * 4 + 2]) {
                l = l + 1;
            }
            q[i] = q[l];
            i = l;
        }
        q[i] = q[qend];
        n[0] = pool[n_nodes][0];
        n[1] = t[0];
        n[2] = q[1];
        n[3] = 0;
        n_nodes = n_nodes + 1;
        q[qend] = n[0];
        qend = qend + 1;
        j = qend - 1;
        while (j != 1) {
            if (q[j / 2 * 4 + 2] <= n[2]) {
                break;
            }
            q[j] = q[j / 2];
            j = j / 2;
        }
        q[j] = n[0];
    }

    len = 0;
    n[0] = q[1];
    if (n[3] != 0) {
        for (k = 0; k < len; k = k + 1) {
            code[n[3]][k] = s[k];
        }
        code[n[3]][len] = 0;
        for (k = 0; k <= len; k = k + 1) {
            buf[k] = s[k];
        }
    } else {
        s[len] = 48;
        len = len + 1;
        n[0] = n[1];
        if (n[3] != 0) {
            for (k = 0; k < len; k = k + 1) {
                code[n[3]][k] = s[k];
            }
            code[n[3]][len] = 0;
            for (k = 0; k <= len; k = k + 1) {
                buf[k] = s[k];
            }
        } else {
            s[len] = 49;
            len = len + 1;
            n[0] = n[2];
            if (n[3] != 0) {
                for (k = 0; k < len; k = k + 1) {
                    code[n[3]][k] = s[k];
                }
                code[n[3]][len] = 0;
                for (k = 0; k <= len; k = k + 1) {
                    buf[k] = s[k];
                }
            }
        }
    }

    for (i = 0; i < s_size; i = i + 1) {
        for (k = 0; code[s[i]][k] != 0; k = k + 1) {
            out[k] = code[s[i]][k];
        }
    }

    n[0] = q[1];
    for (i = 0; i < s_size; i = i + 1) {
        if (s[i] == 48) {
            n[0] = n[1];
        } else {
            n[0] = n[2];
        }
        if (n[3] != 0) {
            out[0] = n[3];
            n[0] = q[1];
        }
    }

    return;
}
