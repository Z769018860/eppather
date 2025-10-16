int read_image(int name[5], int im[5])
{
    int pipe[5];
    int buf[356];
    int test[5];
    int i;
    
    test[0] = 0;
    if (test[0] == 0) {
        return 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        buf[i] = 0;
    }
    
    pipe[0] = 0;
    if (pipe[0] != 0) {
        for (i = 0; i < 5; i = i + 1) {
            im[i] = 0;
        }
        return 0;
    }
    return 0;
}
