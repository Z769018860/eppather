int func() {
    int foo[20];
    int mtime;
    int new_times[2];
    int filename[10] = {'i','n','p','u','t','.','t','x','t','\0'};
    int time_result;
    
    if (stat(filename, foo) < 0) {
        return 1;
    }
    mtime = foo[1];
    
    new_times[0] = foo[0];
    time_result = 0;
    new_times[1] = time_result;
    if (utime(filename, new_times) < 0) {
        return 1;
    }
    
    return 0;
}
