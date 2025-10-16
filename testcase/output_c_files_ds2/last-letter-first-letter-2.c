void store_edge(int nodes_e[26][26], int nodes_out[26][26], int nodes_nout[26], int nodes_in[26][26], int nodes_nin[26], int g_s, int g_e, int g_lnk[26], int g_lnk_idx) {
    if (g_s < 0 || g_e < 0) {
        return;
    }
    int i = g_e;
    int j = g_s;
    int n_e[26];
    for (int k = 0; k < 26; k = k + 1) {
        n_e[k] = nodes_e[j][k];
    }
    g_lnk[g_lnk_idx] = n_e[i];
    nodes_e[j][i] = g_lnk_idx;
    nodes_out[j][i] = nodes_out[j][i] + 1;
    nodes_nout[j] = nodes_nout[j] + 1;
    nodes_in[i][j] = nodes_in[i][j] + 1;
    nodes_nin[i] = nodes_nin[i] + 1;
}

int remove_edge(int nodes_e[26][26], int nodes_out[26][26], int nodes_nout[26], int nodes_in[26][26], int nodes_nin[26], int g_lnk[26], int i, int j) {
    int n_e[26];
    for (int k = 0; k < 26; k = k + 1) {
        n_e[k] = nodes_e[i][k];
    }
    int g = n_e[j];
    if (g >= 0) {
        nodes_e[i][j] = g_lnk[g];
        g_lnk[g] = -1;
        nodes_out[i][j] = nodes_out[i][j] - 1;
        nodes_nout[i] = nodes_nout[i] - 1;
        nodes_in[j][i] = nodes_in[j][i] - 1;
        nodes_nin[j] = nodes_nin[j] - 1;
    }
    return g;
}

int widest(int nodes_out[26][26], int nodes_nout[26], int nodes_in[26][26], int nodes_nin[26], int n, int out) {
    if (nodes_out[n][n] > 0) {
        return n;
    }
    int mm = -1;
    int mi = -1;
    for (int i = 0; i < 26; i = i + 1) {
        if (out > 0) {
            if (nodes_out[n][i] > 0 && nodes_nout[i] > mm) {
                mi = i;
                mm = nodes_nout[i];
            }
        } else {
            if (nodes_out[i][n] > 0 && nodes_nin[i] > mm) {
                mi = i;
                mm = nodes_nin[i];
            }
        }
    }
    return mi;
}

void insert(int c_e[5], int c_tail[5], int c_len[5], int e_lnk[26], int e, int e_idx) {
    e_lnk[e_idx] = c_e[0];
    if (c_tail[0] < 0) {
        c_tail[0] = e_idx;
    }
    c_e[0] = e_idx;
    c_len[0] = c_len[0] + 1;
}

void append(int c_e[5], int c_tail[5], int c_len[5], int e_lnk[26], int e, int e_idx) {
    if (c_tail[0] >= 0) {
        e_lnk[c_tail[0]] = e_idx;
    } else {
        c_e[0] = e_idx;
    }
    c_tail[0] = e_idx;
    c_len[0] = c_len[0] + 1;
}

int shift(int c_e[5], int c_tail[5], int c_len[5], int e_lnk[26]) {
    int e = c_e[0];
    if (e >= 0) {
        c_e[0] = e_lnk[e];
        c_len[0] = c_len[0] - 1;
        if (c_len[0] <= 0) {
            c_tail[0] = -1;
        }
    }
    return e;
}

void make_chain(int nodes_e[26][26], int nodes_out[26][26], int nodes_nout[26], int nodes_in[26][26], int nodes_nin[26], int g_lnk[26], int tmp[5], int s) {
    int c_e[5] = {-1};
    int c_tail[5] = {-1};
    int c_len[5] = {0};
    for (int i = 0; i < 5; i = i + 1) {
        int j = s;
        int k = widest(nodes_out, nodes_nout, nodes_in, nodes_nin, j, 0);
        if (k < 0) {
            break;
        }
        int e = remove_edge(nodes_e, nodes_out, nodes_nout, nodes_in, nodes_nin, g_lnk, k, j);
        if (e < 0) {
            break;
        }
        insert(c_e, c_tail, c_len, g_lnk, e, e);
        j = k;
    }
    for (int i = 0; i < 5; i = i + 1) {
        int j = s;
        int k = widest(nodes_out, nodes_nout, nodes_in, nodes_nin, j, 1);
        if (k < 0) {
            break;
        }
        int e = remove_edge(nodes_e, nodes_out, nodes_nout, nodes_in, nodes_nin, g_lnk, j, k);
        if (e < 0) {
            break;
        }
        append(c_e, c_tail, c_len, g_lnk, e, e);
        j = k;
    }
    for (int step = 0; step < 5; step = step + 1) {
        int e = c_e[0];
        for (int i = 0; i < step; i = i + 1) {
            if (e < 0) {
                break;
            }
            e = g_lnk[e];
        }
        if (e < 0) {
            return;
        }
        int n = 0;
        for (int i = 0; i < 5; i = i + 1) {
            int j = e;
            int k = widest(nodes_out, nodes_nout, nodes_in, nodes_nin, j, 0);
            if (k < 0) {
                break;
            }
            int e2 = remove_edge(nodes_e, nodes_out, nodes_nout, nodes_in, nodes_nin, g_lnk, k, j);
            if (e2 < 0) {
                break;
            }
            tmp[n] = e2;
            n = n + 1;
            j = k;
        }
        if (n > step) {
            for (int i = 0; i < step; i = i + 1) {
                int e3 = shift(c_e, c_tail, c_len, g_lnk);
                if (e3 >= 0) {
                    store_edge(nodes_e, nodes_out, nodes_nout, nodes_in, nodes_nin, e3, e3, g_lnk, e3);
                }
            }
            for (int i = 0; i < n; i = i + 1) {
                insert(c_e, c_tail, c_len, g_lnk, tmp[i], tmp[i]);
            }
            step = -1;
        } else {
            for (int i = n - 1; i >= 0; i = i - 1) {
                store_edge(nodes_e, nodes_out, nodes_nout, nodes_in, nodes_nin, tmp[i], tmp[i], g_lnk, tmp[i]);
            }
        }
    }
    return;
}
