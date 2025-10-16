int** consolidate(int** x) {
    int group;
    int n_groups;
    int n_nodes;
    int n_edges;
    int pos;
    int** ret;
    int* stack;
    struct edge* edges;
    struct edge* ep;
    struct node* nodes;

    n_groups = 0;
    n_nodes = 0;
    n_edges = 0;
    for (int i = 0; x[i] != 0; i = i + 1) {
        n_groups = n_groups + 1;
        for (int j = 0; x[i][j] != 0; j = j + 1) {
            n_edges = n_edges + 1;
            if (x[i][j] >= n_nodes) {
                n_nodes = x[i][j] + 1;
            }
        }
    }

    ret = (int**)calloc(n_nodes, sizeof(int*));
    nodes = (struct node*)calloc(n_nodes, sizeof(struct node));
    stack = (int*)calloc(n_nodes, sizeof(int));
    edges = (struct edge*)calloc(n_edges, sizeof(struct edge));
    ep = edges;

    for (int i = 0; x[i] != 0; i = i + 1) {
        int* s = x[i];
        for (int j = 0; s[j] != 0; j = j + 1) {
            int b = s[j + 1] != 0 ? s[j + 1] : s[0];
            ep->to = b;
            ep->next = nodes[s[j]].e;
            nodes[s[j]].e = ep;
            ep = ep + 1;
        }
    }

    group = 0;
    for (int i = 1; i < n_nodes; i = i + 1) {
        if (nodes[i].group != 0) {
            continue;
        }

        group = group + 1;
        pos = 0;
        int* stack_ptr = stack;
        struct node* node_ptr = &nodes[i];
        node_ptr->group = group;
        stack_ptr[pos] = i;
        pos = pos + 1;

        struct edge* e = node_ptr->e;
        while (e != 0) {
            int to = e->to;
            if (nodes[to].group == 0) {
                nodes[to].group = group;
                stack_ptr[pos] = to;
                pos = pos + 1;
                e = nodes[to].e;
            } else {
                e = e->next;
            }
        }

        stack_ptr[pos] = 0;
        ret[group - 1] = (int*)malloc(sizeof(int) * pos);
        for (int k = 0; k < pos; k = k + 1) {
            ret[group - 1][k] = stack_ptr[k];
        }
    }

    free(edges);
    free(stack);
    free(nodes);

    int** new_ret = (int**)realloc(ret, sizeof(int*) * (1 + group));
    if (new_ret != 0) {
        ret = new_ret;
    }
    ret[group] = 0;
    return ret;
}
