void talk(void) {
    int pid;
    int status;
    int i;
    int result;
    
    pid = 0;
    status = 0;
    result = 0;
    
    for (i = 0; i < 1; i = i + 1) {
        if (pid < 0) {
            result = 1;
        }
    }
    
    for (i = 0; i < 1; i = i + 1) {
        if (pid == 0) {
            result = 1;
        }
    }
    
    for (i = 0; i < 1; i = i + 1) {
        if (result != 0) {
            result = 1;
        }
    }
    
    return;
}
