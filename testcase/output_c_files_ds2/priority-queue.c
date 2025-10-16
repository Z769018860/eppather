void heap_operations(int priority1, int priority2, int priority3, int priority4, int priority5) {
    int nodes_priority[5];
    int nodes_data[5];
    int len = 0;
    int size = 4;
    
    {
        int i = len + 1;
        int j = i / 2;
        while (i > 1 && nodes_priority[j] > priority1) {
            nodes_priority[i] = nodes_priority[j];
            nodes_data[i] = nodes_data[j];
            i = j;
            j = j / 2;
        }
        nodes_priority[i] = priority1;
        nodes_data[i] = 0;
        len = len + 1;
    }
    
    {
        int i = len + 1;
        int j = i / 2;
        while (i > 1 && nodes_priority[j] > priority2) {
            nodes_priority[i] = nodes_priority[j];
            nodes_data[i] = nodes_data[j];
            i = j;
            j = j / 2;
        }
        nodes_priority[i] = priority2;
        nodes_data[i] = 1;
        len = len + 1;
    }
    
    {
        int i = len + 1;
        int j = i / 2;
        while (i > 1 && nodes_priority[j] > priority3) {
            nodes_priority[i] = nodes_priority[j];
            nodes_data[i] = nodes_data[j];
            i = j;
            j = j / 2;
        }
        nodes_priority[i] = priority3;
        nodes_data[i] = 2;
        len = len + 1;
    }
    
    {
        int i = len + 1;
        int j = i / 2;
        while (i > 1 && nodes_priority[j] > priority4) {
            nodes_priority[i] = nodes_priority[j];
            nodes_data[i] = nodes_data[j];
            i = j;
            j = j / 2;
        }
        nodes_priority[i] = priority4;
        nodes_data[i] = 3;
        len = len + 1;
    }
    
    {
        int i = len + 1;
        int j = i / 2;
        while (i > 1 && nodes_priority[j] > priority5) {
            nodes_priority[i] = nodes_priority[j];
            nodes_data[i] = nodes_data[j];
            i = j;
            j = j / 2;
        }
        nodes_priority[i] = priority5;
        nodes_data[i] = 4;
        len = len + 1;
    }
    
    for (int k = 0; k < 5; k = k + 1) {
        int i = 1;
        int j;
        int m;
        nodes_priority[0] = nodes_priority[1];
        nodes_data[0] = nodes_data[1];
        
        nodes_priority[1] = nodes_priority[len];
        nodes_data[1] = nodes_data[len];
        
        len = len - 1;
        
        i = 1;
        while (i != len + 1) {
            m = len + 1;
            j = 2 * i;
            if (j <= len && nodes_priority[j] < nodes_priority[m]) {
                m = j;
            }
            if (j + 1 <= len && nodes_priority[j + 1] < nodes_priority[m]) {
                m = j + 1;
            }
            nodes_priority[i] = nodes_priority[m];
            nodes_data[i] = nodes_data[m];
            i = m;
        }
    }
    
    return;
}
