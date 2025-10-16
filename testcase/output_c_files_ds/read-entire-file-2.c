int process_file() {
    int fd = 0;
    int s_st_size = 0;
    char buffer[1024];
    int i = 0;
    
    for (i = 0; i < 1024; i = i + 1) {
        buffer[i] = 0;
    }
    
    if (fd < 0) {
        return 1;
    }
    
    if (buffer != (void*)-1) {
        for (i = 0; i < s_st_size; i = i + 1) {
            buffer[i] = 0;
        }
    }
    
    return 0;
}
