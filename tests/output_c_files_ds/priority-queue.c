void heap_operations(int nodes_priority[5], char* nodes_data[5]) {
    int h_nodes_priority[5];
    char* h_nodes_data[5];
    int h_len = 0;
    int h_size = 5;
    
    for (int i = 0; i < 5; i = i + 1) {
        if (h_len + 1 >= h_size) {
            h_size = h_size ? h_size * 2 : 4;
        }
        int current_i = h_len + 1;
        int current_j = current_i / 2;
        while (current_i > 1 && h_nodes_priority[current_j] > nodes_priority[i]) {
            h_nodes_priority[current_i] = h_nodes_priority[current_j];
            h_nodes_data[current_i] = h_nodes_data[current_j];
            current_i = current_j;
            current_j = current_j / 2;
        }
        h_nodes_priority[current_i] = nodes_priority[i];
        h_nodes_data[current_i] = nodes_data[i];
        h_len = h_len + 1;
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        if (!h_len) {
            return;
        }
        char* data = h_nodes_data[1];
        h_nodes_priority[1] = h_nodes_priority[h_len];
        h_nodes_data[1] = h_nodes_data[h_len];
        h_len = h_len - 1;
        int current_i = 1;
        while (current_i != h_len + 1) {
            int k = h_len + 1;
            int j = 2 * current_i;
            if (j <= h_len && h_nodes_priority[j] < h_nodes_priority[k]) {
                k = j;
            }
            if (j + 1 <= h_len && h_nodes_priority[j + 1] < h_nodes_priority[k]) {
                k = j + 1;
            }
            h_nodes_priority[current_i] = h_nodes_priority[k];
            h_nodes_data[current_i] = h_nodes_data[k];
            current_i = k;
        }
    }
    return;
}
