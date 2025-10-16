int openimage(const char* s) {
    static int handle = 100;
    int result = handle;
    handle = handle + 1;
    return result;
}
