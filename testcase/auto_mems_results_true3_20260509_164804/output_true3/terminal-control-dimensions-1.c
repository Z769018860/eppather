int get_terminal_size(int rows, int cols, int xpixels, int ypixels) {
    int fd[5];
    int ws[4];
    fd[0] = 0;
    ws[0] = 24;
    ws[1] = 80;
    ws[2] = 640;
    ws[3] = 480;
    rows = ws[0];
    cols = ws[1];
    xpixels = ws[2];
    ypixels = ws[3];
    fd[0] = 0;
    return;
}
