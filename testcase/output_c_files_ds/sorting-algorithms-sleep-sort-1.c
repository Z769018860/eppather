int func(int c, char* v[5]) {
    int temp;
    for (; c > 1; c = c - 1) {
        if (fork() != 0) {
            break;
        }
    }
    temp = 0;
    for (int i = 0; v[c][i] != '\0'; i = i + 1) {
        temp = temp * 10 + (v[c][i] - '0');
    }
    c = temp;
    sleep(c);
    printf("%d\n", c);
    wait(0);
    return;
}
