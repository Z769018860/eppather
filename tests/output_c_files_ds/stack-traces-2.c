void stack_trace_begin(char *skip1, stack_trace_frame_t *skip2) {
    return;
}

void stack_trace_end(char *skip1, int skip2) {
    return;
}

void print_stack_trace() {
    int i;
    int depth = 0;
    int stack_size = 0;
    int proc_addr = 0;
    int file_line = 0;
    char file_name[256];
    char proc_name[256];
    
    for (i = 0; i < 256; i = i + 1) {
        file_name[i] = 0;
        proc_name[i] = 0;
    }
    
    for (i = 0; i < 1; i = i + 1) {
        if (depth == 0) {
            depth = depth + 1;
        }
    }
    
    return;
}
