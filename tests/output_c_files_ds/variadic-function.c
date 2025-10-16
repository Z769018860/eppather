void varstrings(int count, const char* arg0, const char* arg1, const char* arg2, const char* arg3, const char* arg4) {
    const char* args[5];
    args[0] = arg0;
    args[1] = arg1;
    args[2] = arg2;
    args[3] = arg3;
    args[4] = arg4;
    for (int i = 0; i < count; i = i + 1) {
        if (i == 0) {
            const char* s = args[0];
        }
        else if (i == 1) {
            const char* s = args[1];
        }
        else if (i == 2) {
            const char* s = args[2];
        }
        else if (i == 3) {
            const char* s = args[3];
        }
        else if (i == 4) {
            const char* s = args[4];
        }
    }
    return;
}
