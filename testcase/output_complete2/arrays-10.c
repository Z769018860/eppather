int list_ops(int param1, int param2, int param3) {
    int node_value[5];
    int node_next[5];
    int list_first[5];
    int list_size[5];
    int i;
    int j;
    int k;
    
    list_first[0] = 0;
    list_size[0] = 0;
    
    if (param1 != 0) {
        node_value[0] = param2;
        node_next[0] = 0;
        if (list_first[0] == 0) {
            list_first[0] = 1;
        } else {
            i = list_first[0];
            for (j = 0; j < 5; j = j + 1) {
                if (node_next[i] == 0) {
                    break;
                }
                i = node_next[i];
            }
            node_next[i] = 1;
        }
        list_size[0] = list_size[0] + 1;
    }
    
    if (param1 != 0 && list_size[0] > param3) {
        i = list_first[0];
        for (j = 0; j < param3 - 1; j = j + 1) {
            i = node_next[i];
        }
        k = node_next[i];
        node_next[i] = node_next[k];
        list_size[0] = list_size[0] - 1;
    }
    
    if (param1 != 0 && list_size[0] > param3) {
        i = list_first[0];
        for (j = 0; j < param3; j = j + 1) {
            i = node_next[i];
        }
        return node_value[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        node_next[i] = 0;
    }
    list_size[0] = 0;
    
    return 0;
}
