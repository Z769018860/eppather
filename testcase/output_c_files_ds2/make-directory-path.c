void create_dirs(int argc, char** argv) {
    int statBuf[5];
    int s[5];
    int str[5];
    int n1;
    int n2;
    int n3;
    int n4;
    
    n1 = 2;
    if (argc != n1) {
        return;
    }
    s[0] = 1;
    for (n2 = 0; n2 < 5; n2 = n2 + 1) {
        str[0] = s[0];
        if (str[0] != s[0]) {
            str[-1] = 47;
        }
        n3 = -1;
        if (statBuf[0] == n3) {
            n4 = 0;
        } else {
            if (statBuf[0] != 16384) {
                return;
            }
        }
        s[0] = 0;
    }
    return;
}
