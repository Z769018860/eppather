int func(int list_head_value, int next_value) {
    int node_value[1];
    node_value[0] = list_head_value;
    for (int i = 0; i < 1; i = i + 1) {
        if (node_value[i] != 0) {
            node_value[0] = next_value;
        }
    }
    return;
}
