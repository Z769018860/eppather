void rot(int c, int str_len, char str[5]) {
    char alpha_lower[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char alpha_upper[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int i;
    for (i = 0; i < str_len; i = i + 1) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            int pos = str[i] - 'a';
            pos = (pos + c) % 26;
            if (pos < 0) {
                pos = pos + 26;
            }
            str[i] = alpha_lower[pos];
        } else {
            if (str[i] >= 'A' && str[i] <= 'Z') {
                int pos = str[i] - 'A';
                pos = (pos + c) % 26;
                if (pos < 0) {
                    pos = pos + 26;
                }
                str[i] = alpha_upper[pos];
            }
        }
    }
    return;
}
