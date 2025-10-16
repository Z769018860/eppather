int process_file_lines() {
    char line[1024];
    int read;
    int i;
    int j;
    
    for (i = 0; i < 1024; i = i + 1) {
        line[i] = 0;
    }
    
    for (read = 0; read < 1024; read = read + 1) {
        if (line[read] == '\n') {
            for (j = 0; j < read; j = j + 1) {
                line[j] = line[j];
            }
            break;
        }
    }
    
    return;
}
