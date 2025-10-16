int* consolidate(int* x[5], int n_nodes, int n_edges) {
    int group;
    int n_groups;
    int pos;
    int stack[5];
    int ret[5][5];
    int edges[5][2];
    int nodes_group[5];
    int nodes_e[5];
    int ep[2];
    int i;
    int j;
    int a;
    int b;
    int s[5];
    
    n_groups = 0;
    n_nodes = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (x[i] == 0) {
            break;
        }
        n_groups = n_groups + 1;
        for (j = 0; j < 5; j = j + 1) {
            if (x[i][j] == 0) {
                break;
            }
            n_edges = n_edges + 1;
            if (x[i][j] >= n_nodes) {
                n_nodes = x[i][j] + 1;
            }
        }
    }

    for (i = 0; i < 5; i = i + 1) {
        nodes_group[i] = 0;
        nodes_e[i] = 0;
    }

    for (i = 0; i < 5; i = i + 1) {
        if (x[i] == 0) {
            break;
        }
        for (j = 0; j < 5; j = j + 1) {
            if (x[i][j] == 0) {
                break;
            }
            a = x[i][j];
            b = x[i][j + 1] != 0 ? x[i][j + 1] : x[i][0];
            edges[ep[0]][0] = b;
            edges[ep[0]][1] = nodes_e[a];
            nodes_e[a] = ep[0];
            ep[0] = ep[0] + 1;
        }
    }

    group = 0;
    for (i = 1; i < n_nodes; i = i + 1) {
        if (nodes_group[i] != 0) {
            continue;
        }
        group = group + 1;
        pos = 0;
        stack[pos] = i;
        pos = pos + 1;
        nodes_group[i] = group;
        for (j = nodes_e[i]; j != 0; j = edges[j][1]) {
            a = edges[j][0];
            if (nodes_group[a] == 0) {
                stack[pos] = a;
                pos = pos + 1;
                nodes_group[a] = group;
            }
        }
        stack[pos] = 0;
        pos = pos + 1;
        for (j = 0; j < pos; j = j + 1) {
            ret[group - 1][j] = stack[j];
        }
    }

    for (i = 0; i < 5; i = i + 1) {
        if (ret[i][0] == 0) {
            break;
        }
    }
    return ret[0];
}
