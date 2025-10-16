int isValidNetmask(int netmask) {
    int result;
    if (netmask == -1 || netmask == 0) {
        result = 0;
    } else {
        int mask;
        mask = ~netmask;
        mask = mask + 1;
        if ((mask & (mask - 1)) == 0) {
            result = 1;
        } else {
            result = 0;
        }
    }
    return result;
}
