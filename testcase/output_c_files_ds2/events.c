int func(int p[2]) {
    int pid;
    pid = fork();
    if (pid != 0) {
        close(p[0]);
        sleep(1);
        write(p[1], p, 1);
        wait(0);
    } else {
        close(p[1]);
        read(p[0], p + 1, 1);
        puts("received signal from pipe");
    }
    return;
}
