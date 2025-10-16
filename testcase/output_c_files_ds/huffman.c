int encode_decode_huffman(const char input[16], char output[256]) {
    int counts[256] = {0};
    int i;
    int j;
    int k;
    int len;
    int heap_data[256][3];
    int heap_length;
    int heap_capacity;
    int index;
    int parent_index;
    int target;
    int left;
    int right;
    int tree_left[256];
    int tree_right[256];
    int tree_count[256];
    char tree_value[256];
    int tree_size;
    int builder_next_index;
    char builder_str[257];
    char codes[256][257];
    char result[256];
    int result_length;
    int result_index;
    int input_index;
    int current_node;
    
    for (i = 0; i < 256; i = i + 1) {
        counts[i] = 0;
    }
    
    len = 0;
    while (input[len] != '\0') {
        counts[(unsigned char)input[len]] = counts[(unsigned char)input[len]] + 1;
        len = len + 1;
    }
    
    heap_length = 0;
    heap_capacity = 0;
    for (i = 0; i < 256; i = i + 1) {
        if (counts[i] != 0) {
            heap_data[heap_length][0] = i;
            heap_data[heap_length][1] = counts[i];
            heap_data[heap_length][2] = -1;
            heap_length = heap_length + 1;
        }
    }
    
    for (i = 0; i < heap_length; i = i + 1) {
        index = i;
        while (index != 0) {
            parent_index = (index - 1) / 2;
            if (heap_data[parent_index][1] <= heap_data[index][1]) {
                break;
            }
            for (j = 0; j < 3; j = j + 1) {
                k = heap_data[parent_index][j];
                heap_data[parent_index][j] = heap_data[index][j];
                heap_data[index][j] = k;
            }
            index = parent_index;
        }
    }
    
    tree_size = 0;
    while (heap_length > 1) {
        left = heap_data[0][0];
        tree_left[tree_size] = heap_data[0][2];
        for (j = 0; j < 3; j = j + 1) {
            heap_data[0][j] = heap_data[heap_length - 1][j];
        }
        heap_length = heap_length - 1;
        
        index = 0;
        for (;;) {
            target = index;
            left = 2 * index + 1;
            right = left + 1;
            if (left < heap_length && heap_data[left][1] < heap_data[target][1]) {
                target = left;
            }
            if (right < heap_length && heap_data[right][1] < heap_data[target][1]) {
                target = right;
            }
            if (target == index) {
                break;
            }
            for (j = 0; j < 3; j = j + 1) {
                k = heap_data[index][j];
                heap_data[index][j] = heap_data[target][j];
                heap_data[target][j] = k;
            }
            index = target;
        }
        
        right = heap_data[0][0];
        tree_right[tree_size] = heap_data[0][2];
        for (j = 0; j < 3; j = j + 1) {
            heap_data[0][j] = heap_data[heap_length - 1][j];
        }
        heap_length = heap_length - 1;
        
        index = 0;
        for (;;) {
            target = index;
            left = 2 * index + 1;
            right = left + 1;
            if (left < heap_length && heap_data[left][1] < heap_data[target][1]) {
                target = left;
            }
            if (right < heap_length && heap_data[right][1] < heap_data[target][1]) {
                target = right;
            }
            if (target == index) {
                break;
            }
            for (j = 0; j < 3; j = j + 1) {
                k = heap_data[index][j];
                heap_data[index][j] = heap_data[target][j];
                heap_data[target][j] = k;
            }
            index = target;
        }
        
        tree_count[tree_size] = tree_count[left] + tree_count[right];
        tree_left[tree_size] = left;
        tree_right[tree_size] = right;
        heap_data[heap_length][0] = tree_size;
        heap_data[heap_length][1] = tree_count[tree_size];
        heap_data[heap_length][2] = tree_size;
        heap_length = heap_length + 1;
        tree_size = tree_size + 1;
        
        index = heap_length - 1;
        while (index != 0) {
            parent_index = (index - 1) / 2;
            if (heap_data[parent_index][1] <= heap_data[index][1]) {
                break;
            }
            for (j = 0; j < 3; j = j + 1) {
                k = heap_data[parent_index][j];
                heap_data[parent_index][j] = heap_data[index][j];
                heap_data[index][j] = k;
            }
            index = parent_index;
        }
    }
    
    for (i = 0; i < 256; i = i + 1) {
        for (j = 0; j < 257; j = j + 1) {
            codes[i][j] = '\0';
        }
    }
    
    builder_next_index = 0;
    for (i = 0; i < 257; i = i + 1) {
        builder_str[i] = '\0';
    }
    
    current_node = heap_data[0][0];
    if (tree_left[current_node] == -1 && tree_right[current_node] == -1) {
        builder_str[builder_next_index] = '\0';
        for (j = 0; j <= builder_next_index; j = j + 1) {
            codes[tree_value[current_node]][j] = builder_str[j];
        }
    } else {
        builder_str[builder_next_index] = '0';
        builder_next_index = builder_next_index + 1;
        current_node = tree_left[current_node];
        if (tree_left[current_node] == -1 && tree_right[current_node] == -1) {
            builder_str[builder_next_index] = '\0';
            for (j = 0; j <= builder_next_index; j = j + 1) {
                codes[tree_value[current_node]][j] = builder_str[j];
            }
        }
        builder_next_index = builder_next_index - 1;
        
        builder_str[builder_next_index] = '1';
        builder_next_index = builder_next_index + 1;
        current_node = tree_right[current_node];
        if (tree_left[current_node] == -1 && tree_right[current_node] == -1) {
            builder_str[builder_next_index] = '\0';
            for (j = 0; j <= builder_next_index; j = j + 1) {
                codes[tree_value[current_node]][j] = builder_str[j];
            }
        }
        builder_next_index = builder_next_index - 1;
    }
    
    result_length = 0;
    for (i = 0; i < 257; i = i + 1) {
        if (codes[(unsigned char)input[0]][i] == '\0') {
            break;
        }
        result[result_length] = codes[(unsigned char)input[0]][i];
        result_length = result_length + 1;
    }
    result[result_length] = '\0';
    
    input_index = 1;
    while (input[input_index] != '\0') {
        for (i = 0; i < 257; i = i + 1) {
            if (codes[(unsigned char)input[input_index]][i] == '\0') {
                break;
            }
            result[result_length] = codes[(unsigned char)input[input_index]][i];
            result_length = result_length + 1;
        }
        input_index = input_index + 1;
    }
    result[result_length] = '\0';
    
    for (i = 0; i < result_length; i = i + 1) {
        output[i] = result[i];
    }
    output[result_length] = '\0';
    
    return;
}
