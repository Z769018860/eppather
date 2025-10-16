void charListFunc(char* result, int* size, char* elements, int num_elements, int* operations, int num_ops) {
    char list[100];
    int next[100];
    int first = -1;
    int free_index = 0;
    int list_size = 0;
    
    for (int i = 0; i < 100; i = i + 1) {
        next[i] = -1;
    }
    
    for (int op = 0; op < num_ops; op = op + 1) {
        if (operations[op] == 0) {
            if (free_index < 100) {
                list[free_index] = elements[op];
                if (first == -1) {
                    first = free_index;
                } else {
                    int it = first;
                    while (next[it] != -1) {
                        it = next[it];
                    }
                    next[it] = free_index;
                }
                free_index = free_index + 1;
                list_size = list_size + 1;
                result[op] = 0;
            } else {
                result[op] = -1;
            }
        } else if (operations[op] == 1) {
            if (list_size > operations[op + 1] && operations[op + 1] >= 0) {
                int it = first;
                if (operations[op + 1] == 0) {
                    first = next[first];
                } else {
                    for (int i = 0; i < operations[op + 1] - 1; i = i + 1) {
                        it = next[it];
                    }
                    next[it] = next[next[it]];
                }
                list_size = list_size - 1;
                result[op] = 0;
                op = op + 1;
            } else {
                result[op] = -1;
                op = op + 1;
            }
        } else if (operations[op] == 2) {
            if (list_size > operations[op + 1] && operations[op + 1] >= 0) {
                int it = first;
                for (int i = 0; i < operations[op + 1]; i = i + 1) {
                    it = next[it];
                }
                result[op] = list[it];
                op = op + 1;
            } else {
                result[op] = '\0';
                op = op + 1;
            }
        } else if (operations[op] == 3) {
            first = -1;
            free_index = 0;
            list_size = 0;
            for (int i = 0; i < 100; i = i + 1) {
                next[i] = -1;
            }
            result[op] = 0;
        }
    }
    *size = list_size;
    return;
}
