int process_example() {
    int pid;
    int status;
    pid = fork();
    if (pid == 0) {
        for (int i = 0; i < 10000; i = i + 1) {
            continue;
        }
    } else {
        if (pid < 0) {
            status = -1;
        } else {
            wait(&status);
        }
    }
    return;
}
