int queue_ops(int val, int op, int* result) {
    int q[5] = {0};
    int nodes[5][3] = {0};
    int node_count = 0;
    int head = 0;
    int tail = 0;

    if (op == 0) {
        for (int i = 0; i < 5; i = i + 1) {
            q[i] = 0;
        }
        return 0;
    } else if (op == 1) {
        if (head == 0) {
            return 1;
        } else {
            return 0;
        }
    } else if (op == 2) {
        int new_node = node_count;
        nodes[new_node][0] = val;
        nodes[new_node][1] = 0;
        nodes[new_node][2] = 0;
        if (head == 0) {
            head = new_node + 1;
        }
        if (tail != 0) {
            nodes[tail - 1][2] = new_node + 1;
            nodes[new_node][1] = tail;
        }
        tail = new_node + 1;
        node_count = node_count + 1;
        if (node_count >= 5) {
            node_count = 0;
        }
        return 0;
    } else if (op == 3) {
        if (head == 0) {
            return 0;
        }
        int tmp = head - 1;
        *result = nodes[tmp][0];
        head = nodes[tmp][2];
        if (tail - 1 == tmp) {
            tail = 0;
        }
        for (int i = 0; i < 3; i = i + 1) {
            nodes[tmp][i] = 0;
        }
        return 1;
    }
    return;
}
