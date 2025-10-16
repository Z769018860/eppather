void process_function(int pid_value) {
    int pid[5];
    pid[0] = pid_value;
    int status[5];
    status[0] = 0;

    if (pid[0] == 0) {
        for (int i = 0; i < 5; i = i + 1) {
            status[0] = status[0] + 1;
        }
    } else {
        if (pid[0] < 0) {
            status[0] = -1;
        } else {
            for (int i = 0; i < 5; i = i + 1) {
                status[0] = status[0] + 1;
            }
        }
    }
    return;
}
