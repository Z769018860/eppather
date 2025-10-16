int huffman_code(int input_len, int input[5], int tree_left[5], int tree_right[5], int tree_count[5], int tree_value[5], int builder_str[257], int builder_next_index, int codebook_codes[256][257]) {
    int counts[256];
    for (int i = 0; i < 256; i = i + 1) {
        counts[i] = 0;
    }
    for (int i = 0; i < input_len; i = i + 1) {
        counts[input[i]] = counts[input[i]] + 1;
    }
    int heap_data[256][5];
    int heap_length = 0;
    int heap_capacity = 0;
    for (int i = 0; i < 256; i = i + 1) {
        if (counts[i] != 0) {
            tree_value[heap_length] = i;
            tree_count[heap_length] = counts[i];
            tree_left[heap_length] = -1;
            tree_right[heap_length] = -1;
            for (int j = 0; j < 5; j = j + 1) {
                heap_data[heap_length][j] = 0;
            }
            heap_data[heap_length][0] = heap_length;
            heap_length = heap_length + 1;
        }
    }
    if (heap_length == 1) {
        int leaf = heap_data[0][0];
        tree_left[heap_length] = leaf;
        tree_count[heap_length] = tree_count[leaf];
        tree_value[heap_length] = 0;
        tree_right[heap_length] = -1;
        return heap_length;
    }
    while (heap_length > 1) {
        int left = heap_data[0][0];
        for (int i = 0; i < heap_length - 1; i = i + 1) {
            for (int j = 0; j < 5; j = j + 1) {
                heap_data[i][j] = heap_data[i + 1][j];
            }
        }
        heap_length = heap_length - 1;
        int right = heap_data[0][0];
        for (int i = 0; i < heap_length - 1; i = i + 1) {
            for (int j = 0; j < 5; j = j + 1) {
                heap_data[i][j] = heap_data[i + 1][j];
            }
        }
        heap_length = heap_length - 1;
        tree_left[heap_length] = left;
        tree_right[heap_length] = right;
        tree_count[heap_length] = tree_count[left] + tree_count[right];
        tree_value[heap_length] = 0;
        heap_data[heap_length][0] = heap_length;
        heap_length = heap_length + 1;
    }
    int root = heap_data[0][0];
    for (int i = 0; i < 257; i = i + 1) {
        builder_str[i] = 0;
    }
    builder_next_index = 0;
    for (int i = 0; i < 256; i = i + 1) {
        for (int j = 0; j < 257; j = j + 1) {
            codebook_codes[i][j] = 0;
        }
    }
    int stack[256];
    int stack_top = 0;
    stack[stack_top] = root;
    stack_top = stack_top + 1;
    while (stack_top > 0) {
        stack_top = stack_top - 1;
        int node = stack[stack_top];
        if (tree_left[node] == -1 && tree_right[node] == -1) {
            builder_str[builder_next_index] = 0;
            for (int i = 0; i <= builder_next_index; i = i + 1) {
                codebook_codes[tree_value[node]][i] = builder_str[i];
            }
        } else {
            builder_str[builder_next_index] = 48;
            builder_next_index = builder_next_index + 1;
            stack[stack_top] = node;
            stack_top = stack_top + 1;
            stack[stack_top] = tree_left[node];
            stack_top = stack_top + 1;
            builder_next_index = builder_next_index - 1;
            builder_str[builder_next_index] = 49;
            builder_next_index = builder_next_index + 1;
            stack[stack_top] = node;
            stack_top = stack_top + 1;
            stack[stack_top] = tree_right[node];
            stack_top = stack_top + 1;
            builder_next_index = builder_next_index - 1;
        }
    }
    return root;
}
